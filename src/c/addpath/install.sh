#!/bin/sh

#installs addtopath...

echo "Checking operating system"
if [ `uname` != "Darwin" ]
then
    echo "addtopath is only aimed at Mac users."
    exit 1
fi
if [ "$(id -u)" != "0" ]
then
    echo "This installer must be run as root."
    exit 1
fi
echo "This installs addtopath. Please note that Xcode (and UNIX Development) must be installed in other to be able to run gcc which is needed to compile addtopath."
isgccinstalled=`which gcc`
if [ "$isgccinstalled" == "" ]
then
    echo ""
    echo "It doesn't seem like gcc is installed or added to the PATH variable."
    echo "If you use Xcode 3, go to /Developer/Library/ and run uninstall-devtools --mode=all as root (this command uninstalls Xcode) and then reinstall Xcode. When reinstalling, after accepting the license agreements, please click Customize and make sure that the 'UNIX Development' checkbox is checked."
    echo ""
    echo "If you are using Xcode 4, uninstall Xcode 4 by running /Developer/Library/uninstall-devtools --mode=all, and then reinstall Xcode 4 right-clicking (or ctrl-clicking) the Xcode Installer (if you don't have the installer, it is available on the Mac App Store) and click 'Show Package Content' on the menu that appears. On the 'new' Finder window, go to 'Resources' and then open 'Xcode and iPhone SDK'. When running the installer, after accepting the license agreements, click the 'Customize' button and then make sure that the 'UNIX Development' checkbox is checked."
    exit 1
fi
gcc -o /usr/bin/addtopath main.c

cp addtopath.1 /usr/share/man/man1/addtopath.1
