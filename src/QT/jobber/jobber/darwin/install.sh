#!/bin/sh

if [ -e "/opt/local/Qt/5.9.2/clang_64/bin/qmake" ]
then
    /opt/local/Qt/5.9.2/clang_64/bin/qmake -o Makefile ../jobber.pro -spec macx-clang
    /usr/bin/make
    /bin/rm -f install
    /bin/cp -R jobber.app/ /Applications/jobber.app/
    /usr/bin/make clean
else
    echo "Please install QT5 by typing `port install qt5.x`, e.g. qt5.9."
    exit 1
fi
