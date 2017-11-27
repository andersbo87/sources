#!/bin/sh
if [ $(id -u) != 0 ]
then
    echo "This script must be run as root."
    exit 1
fi

if [ -e /usr/local/lib/qt5/bin/qmake ]
then
    /usr/local/lib/qt5/bin/qmake -spec freebsd-clang -o Makefile ../jobber.pro
    make install clean
    rm -f install
else
    echo "Please install all of QT5 using `pkg install qt5` or cd `/usr/ports/devel/qt5/ && make install clean`."
    exit 1
fi
