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

echo "Installing into $prefix...."

sudo cp ./bfc $prefix

echo "Installed!"

