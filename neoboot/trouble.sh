#!/bin/bash

#固定変数(変えると動かなくなります)
script_dir="$(dirname "$(readlink -f "$0")")"

rm neos.img neos.img.dmg