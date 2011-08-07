WHY
===

I could not find a legit compiler for unix/osx so I made my own
I use the bf2c (brainfuck to c) dependency to convert the brainfuck to c code then compile using gcc
Basically it's a convenience thing but all in one repo

Feel free to use and distribute but pl0x use my name

Thanks

SCRIPTS
=======

doit.sh will install everything necessary, create a hello world program in brainfuck, compile it and then run it
setup.sh will update the submodules if necessary, and proceed to install bf2c
install.sh will install bfc - can take one parameter for a prefix ex: install.sh /bin/
uninstall.sh will uninstall bfc (note not bf2c) - can take one parameter ex: uninstall.sh /bin/

