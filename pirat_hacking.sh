#!/bin/bash

git clone --branch pirathavn https://github.com/krulf/pirathak.git pirathavn

if [ ! -d /etc/apt/keyrings ]; then
	sudo mkdir -p /etc/apt/keyrings
fi

if [ ! -f /etc/apt/keyrings/charm.gpg ]; then
	curl -fsSL https://repo.charm.sh/apt/gpg.key | sudo gpg --dearmor -o /etc/apt/keyrings/charm.gpg
	echo "deb [signed-by=/etc/apt/keyrings/charm.gpg] https://repo.charm.sh/apt/ * *" | sudo tee /etc/apt/sources.list.d/charm.list
fi

dpkg -s glow #is glow installed?
if [[ $? == 1 ]]; then
	sudo apt update && sudo apt install glow
fi

dpkg -s libmikmod3 #is libmikmod installed?
if [[ $? == 1 ]]; then
	sudo apt update && sudo apt install libmikmod3
fi

source pirathavn/.aliasdef

clear
hjælp
# if using bash bash --rcfile <(cat $HOME/.bashrc; echo 'export PROMPT_COMMAND="cd pirathak;source aliasdef; echo Skriv start;export PROMPT_COMMAND="') -i
