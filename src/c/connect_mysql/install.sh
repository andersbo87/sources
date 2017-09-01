#!/bin/sh
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi
#echo "Dette installerer Little House Dictionary på datamaskinen din."
#echo "For at dette skal gå greit for seg, må du oppgi noen opplysninger."
$incl
incl=`mysql_config --include`
#printf "Skriv inn teksten som begynte med -I på linjen ovenfor: "
#read incl
$lib
lib=`mysql_config --libs`
#printf "Skriv inn teksten på linjen over som begynner med -L: "
#read lib

gcc $incl $lib -o lhd lhd.c add_word.c remove_word.c search_word.c update_word.c
cp lhd /usr/bin/lhd
cp lhd.1.gz /usr/share/man/man1/lhd.1.gz