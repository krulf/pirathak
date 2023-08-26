#!/bin/bash
# For arch linux

git clone https://github.com/krulf/pirathak.git

sudo pacman -S glow

alias opgave3='echo "# Sådan det køre....\n\n### virker det..?" >> næste_opgave.md | glow næste_opgave.md'

cd pirathak/Terminal-træning
clear
glow Introduktion.md
