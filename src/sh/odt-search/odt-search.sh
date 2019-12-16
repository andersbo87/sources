#!/bin/sh

find . -type f -name "*.od*" | while read i ; do
   [ "$1" ] || { echo "You forgot search string!" ; exit 1 ; }
   unzip -ca "$i" 2>/dev/null | grep -iq "$*"
   if [ $? -eq 0 ] ; then
      echo "string found in $i" | nl
   fi
done
