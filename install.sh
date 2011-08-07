#!/bin/bash

prefix=/usr/bin/

if [ -z `which bf2c` ]; then
	echo "Either manually install bf2c or run ./setup.sh"
	exit 1
fi

if [ $2 ]; then
	echo "Usage: $0 [prefix]"
	exit 1
fi

if [ $1 ]; then
        echo "Setting prefix $1"
        prefix=$1
fi

echo "Installing into $prefix.... (will ask for root (or admin on osx) pass so I can properly install into the system)"

sudo cp ./bfc $prefix

echo "Installed!"

