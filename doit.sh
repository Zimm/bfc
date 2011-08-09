#!/bin/bash

echo "This script will install everything, make a hello world brainfuck file compile it, then run it"
echo ""
./compile.sh
echo ""
./install.sh
echo "Creating helloworld...."
echo ""
echo "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>." > helloworld.bf
echo "Compiling helloworld...."
echo ""
bfc helloworld.bf helloworld
echo ""
sleep 1
./helloworld

