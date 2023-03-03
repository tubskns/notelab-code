## Troubleshooting

### k3s

#### Install 

```shell
curl -sfL https://get.k3s.io | INSTALL_K3S_VERSION=v1.20.9+k3s1 sh -
```

#### Fix permissions

To fix `k3s` permissions, run the following command (or add it to your `.bashrc` or `.zshrc`):

```shell
sudo cp /etc/rancher/k3s/k3s.yaml ~/.kube/k3s-config && sudo chown $USER: ~/.kube/k3s-config && export KUBECONFIG=~/.kube/k3s-config
```

#### Uninstall

```shell
/usr/local/bin/k3s-uninstall.sh
```
