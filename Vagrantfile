# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Every Vagrant development environment requires a box. You can search for
  # boxes at https://vagrantcloud.com/search.
  config.vm.box = "archlinux/archlinux"

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  config.vm.box_check_update = true

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # NOTE: This will enable public access to the opened port
  # config.vm.network "forwarded_port", guest: 3000, host: 8080

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine and only allow access
  # via 127.0.0.1 to disable public access
  config.vm.network "forwarded_port", guest: 3000, host: 8080, host_ip: "127.0.0.1"

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  # config.vm.synced_folder "../data", "/vagrant_data"

  # Disable the default share of the current code directory. Doing this
  # provides improved isolation between the vagrant box and your host
  # by making sure your Vagrantfile isn't accessable to the vagrant box.
  # If you use this you may want to enable additional shared subfolders as
  # shown above.
  # config.vm.synced_folder ".", "/home/vagrant/pirathavn", :mount_options => ["dmode=777","fmode=666"]

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  # config.vm.provider "virtualbox" do |vb|
  #   # Display the VirtualBox GUI when booting the machine
  #   vb.gui = true
  #
  #   # Customize the amount of memory on the VM:
  #   vb.memory = "1024"
  # end
  #
  # View the documentation for the provider you are using for more
  # information on available options.

  # Enable provisioning with a shell script. Additional provisioners such as
  # Ansible, Chef, Docker, Puppet and Salt are also available. Please see the
  # documentation for more information about their specific syntax and use.
  config.vm.provision "shell", inline: <<-SHELL

    pacman -Qo nano
    if [[ $? == 1 ]]
    then
       echo "nano is missing"
       sudo pacman -S --noconfirm nano
    fi
    
    pacman -Qo git
    if [[ $? == 1 ]]
    then
       echo "Git is missing"
       sudo pacman -S --noconfirm git
    fi

    git clone --branch pirathavn https://github.com/krulf/pirathak.git pirathavn

    pacman -Qo nodejs
    if [[ $? == 1 ]]
    then
       echo "Nodejs is missing"
       sudo pacman -S --noconfirm nodejs npm
    fi

    pacman -Qo cupp-v3
    if [[ $? == 1 ]]
    then
       echo "Cupp is missing"
       sudo pacman -S --noconfirm cupp-v3
    fi

    pacman -Qo fcrackzip
    if [[ $? == 1 ]]
    then
       echo "Fcrackzip is missing"
       sudo pacman -S --noconfirm fcrackzip
    fi

    pacman -Qo crunch
    if [[ $? == 1 ]]
    then
       echo "Crunch is missing"
       sudo pacman -S --noconfirm crunch
    fi

    pacman -Qo glow
    if [[ $? == 1 ]]
    then
       echo "Glow is missing"
       sudo pacman -S --noconfirm glow
    fi

    pacman -Qo glow
    if [[ $? == 1 ]]
    then
       echo "Glow is missing"
       sudo pacman -S --noconfirm glow
    fi

    pacman -Qo unzip
    if [[ $? == 1 ]]
    then
       echo "Unzip is missing"
       sudo pacman -S --noconfirm unzip
    fi

    pacman -Qo tree
    if [[ $? == 1 ]]
    then
       echo "Tree is missing"
       sudo pacman -S --noconfirm tree
    fi

    pacman -Qo xdg-utils
    if [[ $? == 1 ]]
    then
       echo "XDG-utils is missing"
       sudo pacman -S --noconfirm xdg-utils
    fi

    pacman -Qo libmikmod3
    if [[ $? == 1 ]]
    then
       echo "libmikmod3 is missing"
       sudo pacman -S --noconfirm libmikmod3
    fi

    echo "sudo chown -R vagrant pirathavn > /dev/null">> /home/vagrant/.bashrc
    
    echo "source pirathavn/.aliasdef">> /home/vagrant/.bashrc
    echo "sleep 0.5">> ~/.bashrc
    echo "glow pirathavn/.intro.md">> /home/vagrant/.bashrc
   #    echo "cd pirathavn">> /home/vagrant/.bashrc
    
    SHELL

    # config.vm.provision "shell", inline: "chmod +x pirathavn/.aliasdef && pirathavn/.aliasdef"
    # config.vm.provision "shell", inline: "glow pirathavn/.intro.md"

end
