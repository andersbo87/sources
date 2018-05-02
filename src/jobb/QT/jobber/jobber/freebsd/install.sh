#!/bin/sh

checkroot(){
    # Sjekke om brukeren er rotbruker eller ikke.
    if [ $(id -u) != 0 ]
    then
	echo "This script must be run as root."
	exit 1
    fi
}

if [ -e /usr/local/lib/qt5/bin/qmake ]
then
    /usr/local/lib/qt5/bin/qmake -spec freebsd-clang -o ../Makefile ../jobber.pro
else
    echo "Please install all of QT5 using `pkg install qt5` or cd `/usr/ports/devel/qt5/ && make install clean`."
    exit 1
fi
if [ "$1" == "uninstall" ]
then
    checkroot
    make -C ../ uninstall clean
    rm ../Makefile
elif [ "$1" == "compile" ]
then
    make -C ../
    rm ../Makefile
elif [ "$1" == "clean" ]
then
    make -C ../ clean
    rm ../Makefile
else
    checkroot
    make -C ../ install clean
    rm -f install
    rm ../Makefile
fi
