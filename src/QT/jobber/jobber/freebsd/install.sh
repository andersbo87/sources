#!/bin/sh
if [ $(id -u) != 0 ]
then
    echo "This script must be run as root."
    exit 1
fi

if [ -e /usr/local/lib/qt5/bin/qmake ]
then
    /usr/local/lib/qt5/bin/qmake -spec freebsd-clang -o ../Makefile ../jobber.pro
else
    echo "Please install all of QT5 using `pkg install qt5` or cd `/usr/ports/devel/qt5/ && make install clean`."
    exit 1
fi

if [ "$1" != "uninstall" ]
then
    make -C ../ install clean
    rm -f install
    rm ../Makefile
else
    make -C ../ uninstall clean
    rm ../Makefile
fi
