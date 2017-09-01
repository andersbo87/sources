#!/bin/sh

for dir in $1 $2 $3
do
    cd $dir
    echo "Bytter til $dir"
    for file in *
    do
	if [ -f $file -a -r $file -a -w $file ]
	then
	    echo "Sorterer $file"
	    sort -o $file $file
	fi
    done
    cd ..
done