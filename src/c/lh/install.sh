#!/bin/sh

#a shell script that installs the little house database into the system...
if [ "$(id -u)" != "0" ]
then
    echo "This script must be run as root" 1>&2
    exit 1
fi
$incl
incl=`mysql_config --include`
$lib
lib=`mysql_config --libs`

gcc $incl $lib -lreadline -o lh main.c
cp lh /usr/bin/lh
chmod ugo+x /usr/bin/lh
#cp lh.1.gz /usr/share/man/man1/lh.1.gz