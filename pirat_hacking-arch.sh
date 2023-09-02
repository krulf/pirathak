#!/bin/bash
# For arch linux
#

sudo pacman -S --needed glow

git clone --branch pirathavn https://github.com/krulf/pirathak.git pirathavn

source aliasdef
start
$SHELL
