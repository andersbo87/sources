#!/bin/sh

if [ $(id -u) != 0 ]
then
    echo "This script must be run as root."
    exit 1
fi

if [ -e "/usr/lib/x86_64-linux-gnu/qt5/bin/qmake" ]
then
    /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -o ../Makefile ../jobber.pro -spec linux-clang
    make -C ../
    make -C ../ install clean
    rm -f install ../Makefile
else
    echo "Please install QT5 before running this script."
fi
