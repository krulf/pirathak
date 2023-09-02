#!/bin/bash

git clone https://github.com/krulf/pirathak.git

sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://repo.charm.sh/apt/gpg.key | sudo gpg --dearmor -o /etc/apt/keyrings/charm.gpg
echo "deb [signed-by=/etc/apt/keyrings/charm.gpg] https://repo.charm.sh/apt/ * *" | sudo tee /etc/apt/sources.list.d/charm.list
sudo apt update && sudo apt install glow

alias opgave3='echo "# Sådan det køre....\n\n### virker det..?" >> næste_opgave.md | glow næste_opgave.md'

cd pirathak/Terminal-træning
clear
glow Introduktion.md
