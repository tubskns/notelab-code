#!/bin/bash

# Script to create a custom Ubuntu autoinstall ISO for Ubuntu 24.04
# Assumes ubuntu-24.04.1-live-server-amd64.iso and autoinstall.yaml are in the current directory

# Exit immediately if a command exits with a non-zero status
set -e

# Variables
UBUNTU_VERSION="24.04.4"


ISO_NAME="ubuntu-${UBUNTU_VERSION}-desktop-amd64.iso"
ISO_URL="https://releases.ubuntu.com/${UBUNTU_VERSION}/${ISO_NAME}"
ISO_CUSTOM="$(pwd)/ubuntu-24.04.4-autoinstall.iso"
WORK_DIR="$(pwd)/ubuntu-autoinstall"
MOUNT_DIR="$WORK_DIR/mount"
ISO_DIR="$WORK_DIR/iso"
NOCLOUD_DIR="$ISO_DIR/nocloud"
AUTOINSTALL_FILE="autoinstall.yaml"

# Check for required files
if [[ ! -f "$ISO_NAME" ]]; then
  echo "ISO file '$ISO_NAME' not found in the current directory."
  read -r -p "Download it from $ISO_URL? [Y/n] " REPLY
  case "$REPLY" in
    ""|[Yy]|[Yy][Ee][Ss])
      echo "Downloading $ISO_NAME..."
      # Download to a temporary name so an interrupted download is not mistaken for a complete ISO
      if command -v curl >/dev/null 2>&1; then
        curl -fL --progress-bar -o "$ISO_NAME.part" "$ISO_URL"
      elif command -v wget >/dev/null 2>&1; then
        wget -O "$ISO_NAME.part" "$ISO_URL"
      else
        echo "Neither curl nor wget is installed. Please download the ISO manually."
        exit 1
      fi
      mv "$ISO_NAME.part" "$ISO_NAME"
      echo "Download complete."
      ;;
    *)
      echo "ISO is required to continue. Aborting."
      exit 1
      ;;
  esac
fi

if [[ ! -f "$AUTOINSTALL_FILE" ]]; then
  echo "Autoinstall file '$AUTOINSTALL_FILE' not found in the current directory."
  exit 1
fi

# Install required packages
echo "Installing required packages..."
# sudo apt-get update
# sudo apt-get install -y xorriso grub-pc-bin grub-efi-amd64-bin grub-efi-ia32-bin mtools rsync

# Create working directories
echo "Creating working directories..."
mkdir -p "$MOUNT_DIR" "$ISO_DIR"

# Mount the original ISO
echo "Mounting the original ISO..."
sudo mount -o loop "$ISO_NAME" "$MOUNT_DIR"

# Copy the contents of the ISO to the working directory
echo "Copying ISO contents..."
sudo rsync -a -v "$MOUNT_DIR/" "$ISO_DIR/"

# Unmount the ISO
echo "Unmounting the original ISO..."
sudo umount "$MOUNT_DIR"

# Change ownership to current user for editing
echo "Adjusting permissions..."
sudo chown -R "$(whoami):$(whoami)" "$ISO_DIR/"
sudo chmod -R u+w "$ISO_DIR/"

# Copy autoinstall.yaml to the root of the ISO
echo "Adding autoinstall and nocloud configuration..."
# Create the cloud-init folders
mkdir -p "$NOCLOUD_DIR"
touch "$NOCLOUD_DIR/meta-data"
cp "$AUTOINSTALL_FILE" "$NOCLOUD_DIR/user-data"

# Modify GRUB configuration for both BIOS and UEFI boot
echo "Modifying GRUB configuration..."
GRUB_CFG="$ISO_DIR/boot/grub/grub.cfg"
sudo tee "$GRUB_CFG" >/dev/null <<EOF
set timeout=30

loadfont unicode

set menu_color_normal=white/black
set menu_color_highlight=black/light-gray

menuentry "Ubuntu with NoTED Lab Software" {
	set gfxpayload=keep
	linux	/casper/vmlinuz autoinstall ds=nocloud\;s=/cdrom/nocloud --- quiet splash
	initrd	/casper/initrd
}
menuentry "Ubuntu with NoTED Lab Software (safe graphics)" {
	set gfxpayload=keep
	linux	/casper/vmlinuz nomodeset autoinstall ds=nocloud\;s=/cdrom/nocloud --- quiet splash
	initrd	/casper/initrd
}
grub_platform
if [ "$grub_platform" = "efi" ]; then
menuentry 'Boot from next volume' {
	exit 1
}
menuentry 'UEFI Firmware Settings' {
	fwsetup
}
else
menuentry 'Test memory' {
	linux16 /boot/memtest86+x64.bin
}
fi
EOF

# Create GRUB EFI image
echo "Creating GRUB EFI image..."
mkdir -p "$ISO_DIR/EFI/boot"
grub2-mkstandalone \
  --format=x86_64-efi \
  --output="$ISO_DIR/EFI/boot/bootx64.efi" \
  --locales="" \
  --fonts="" \
  "boot/grub/grub.cfg=$GRUB_CFG"

# Create UEFI boot image
echo "Creating UEFI boot image..."
dd if=/dev/zero of="$ISO_DIR/boot/grub/efi.img" bs=1M count=10
mkfs.vfat "$ISO_DIR/boot/grub/efi.img"
mmd -i "$ISO_DIR/boot/grub/efi.img" efi efi/boot
mcopy -i "$ISO_DIR/boot/grub/efi.img" "$ISO_DIR/EFI/boot/bootx64.efi" ::efi/boot/

# Updating MD5 checksums
echo "Updating MD5 checksums..."
cd "$ISO_DIR"
sudo chmod u+w md5sum.txt
sudo rm md5sum.txt
sudo find . -type f ! -name 'md5sum.txt' ! -path './ubuntu/*' -exec md5sum {} \; | sudo tee md5sum.txt

# Create the new ISO image
echo "Creating the custom ISO..."
cd "$WORK_DIR"
xorriso -as mkisofs \
  -iso-level 3 \
  -o "$ISO_CUSTOM" \
  -full-iso9660-filenames \
  -volid "UBUNTU_24_04_1_SERVER_AMD64" \
  -eltorito-boot boot/grub/i386-pc/eltorito.img \
  -no-emul-boot \
  -boot-load-size 4 \
  -boot-info-table \
  -eltorito-alt-boot \
  -e boot/grub/efi.img \
  -no-emul-boot \
  -isohybrid-gpt-basdat \
  "$ISO_DIR"

# Clean up
echo "Cleaning up temporary files..."
sudo rm -rf "$WORK_DIR"

echo "Custom autoinstall ISO created successfully: $ISO_CUSTOM"
