#!/bin/bash

prefix=/usr/bin/

if [ -e "./build/bfc" ]; then

if [ $2 ]; then
	echo "Usage: $0 [prefix]"
	exit 1
fi

if [ $1 ]; then
        echo "Setting prefix $1"
        prefix=$1
fi

echo "Installing into $prefix.... (will ask for root (or admin on osx) pass so I can properly install into the system)"

sudo cp ./build/bfc $prefix

echo "Installed!"
else
echo "Please run ./compile.sh first then run this, or just run ./doit.sh"
exit 1
fi

