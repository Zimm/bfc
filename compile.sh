#!/bin/bash
#put in some checks for necessary files pl0x
echo "Compiling...."
mkdir -p build
g++ -O3 -Wabi -Wctor-dtor-privacy -Wreorder -Weffc++ -Wstrict-null-sentinel -Woverloaded-virtual -pedantic-errors -w -Wall -Werror -Wfatal-errors -Wnonnull -Wformat=2 -Wmissing-braces -DGCC_PATH=\"`which gcc`\" bfc.cpp -o build/bfc
if [ $? == 0 ]; then
echo "Success!"
else
echo "Failed to compile D:"
fi
