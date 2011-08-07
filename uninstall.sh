#!/bin/bash

prefix=/usr/bin/

if [ $2 ]; then
	echo "Usage: $0 [prefix]"
	exit 1
fi

if [ $1 ]; then
        echo "Setting prefix $1"
        prefix=$1
fi

echo "Uninstalling from $prefix.... (will ask for root (or admin on osx) pass so I can properly uninstall from the system)"

sudo rm ${prefix}bfc

echo "Uninstalled!"

