#!/bin/bash
# For arch linux
#

sudo pacman -S glow

git clone https://github.com/krulf/pirathak.git

# Sæt hjem
hjem=$(pwd)/pirathak

# Sæt hjælp og nulstil til første opgave
alias hjælp='glow $hjem/Terminal-træning/intro.md'
alias start='clear && cd $hjem/Terminal-træning && glow intro.md'

alias opgave3='echo "# Sådan det køre....\n\n### virker det..?" >> næste_opgave.md | glow næste_opgave.md'

start
