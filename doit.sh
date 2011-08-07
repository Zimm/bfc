#!/bin/bash

echo "This script will install everything, make a hello world brainfuck file compile it, then run it"

./setup.sh
./install.sh
echo "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>." > helloworld.bf
bfc helloworld.bf helloworld
./helloworld

