## Administration tasks

### VMs using Vagrant

If required, edit `vms_param.rb` accordingly.

Vagrant cheat sheet:

- `vagrant up` -- starts vagrant environment.
- `vagrant ssh <boxname>` -- connects to machine via SSH.
- `vagrant suspend` -- suspends a virtual machine.
- `vagrant resume` -- resumes a suspended machine. 
- `vagrant halt` -- stops the vagrant machine.
- `vagrant destroy` -- deletes all traces of the vagrant machine.

### (Debugging) Auto-deployment of RabbitMQ + Logstash + Elasticsearch

Run the following script to deploy all tools:

```
./deploy_helper.sh -rel
```

Uninstall everything with:

```
./deploy_helper.sh -u
```

### Auto-install Ubuntu ISO image

1. Clone `pxeless` repo and copy `user-data-server` or `user-data-desktop` into it:

    ``` shell
    git clone https://github.com/cloudymax/pxeless.git
    cp user-data-server pxeless/
    cp user-data-desktop pxeless/
    ```

2. Edit `user-data-*` (if required). To change password, generate it with
  `mkpasswd -m sha-512`.

3. Run `pxeless`:
    ```
    ./image-create.sh -a -u user-data-server -n jammy -d notelab-ubuntu-server.iso
    ```
    or
    ```
    ./image-create.sh -a -u user-data-desktop -n jammy -d notelab-ubuntu-desktop.iso
    ```

    Wait until the ISO file is created.