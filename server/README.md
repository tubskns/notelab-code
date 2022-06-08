## Server

Deployment of RabbitMQ + Logstash + Elasticsearch using K3s

### Deployment of VMs for running isolated instances

1. Edit `vms_param.rb` accordingly
2. Run `vagrant up` to deploy VMs
3. Run `vagrant ssh worker1` or `workerX` to access to each specific VM.
4. `vagrant halt` to shutdown all VMs
5. `vagrant destroy` to delete all VMs


### Debugging

For debugging purposes, run the following script for the automated deployment of
all necessary tools and configuration:

```
./deploy_helper.sh -rel
```

Uninstall everything with:

```
./deploy_helper.sh -u
```