#!/bin/bash

if [ -e "./bf2c/bootstrap.sh" ]; then
	git submodule update --init --recursive
fi
cd bf2c
./bootstrap.sh
./configure
make
echo "I will now ask for the root password (or your admin pass on osx) so that I can install bf2c"
sudo make install
cd ..
echo "Setup went well, continue on to install.sh"
exit 0
