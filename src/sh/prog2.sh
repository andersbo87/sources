#!/bin/sh

n_files=0

for file in `ls`
do
    echo hei
    ((n_files=n_files+1))
done

echo $n_files