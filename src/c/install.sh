#!/bin/sh
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi
#sjekke hva slags OS brukeren kjører…
CC=""
echo "Ser etter en komatibel C-kompilator"
if [ -a /usr/bin/gcc ]
then
    echo gcc
    cc="gcc"
elif [ -a /usr/bin/cc ]
then
    echo cc
    cc="cc"
else
    exit 1
fi
echo "Sjekker hvilket operativsystem som er installert… "
OS=$(uname)
echo $OS
if [ "$OS" == "Darwin" ]
then
    $cc -I/usr/include/mysql  -g -Os -arch x86_64 -fno-common   -D_P1003_1B_VISIBLE -DSIGNAL_WITH_VIO_CLOSE -DSIGNALS_DONT_BREAK_READ -DIGNORE_SIGHUP_SIGQUIT  -DDONT_DECLARE_CXA_PURE_VIRTUAL -L/usr/lib/mysql -lmysqlclient -lz -lm -o /usr/bin/lhd lhd.c remove_word.c search_word.c add_word.c update_word.c
   # $cc -I/usr/include/mysql  -g -Os -arch x86_64 -fno-common   -D_P1003_1B_VISIBLE -DSIGNAL_WITH_VIO_CLOSE -DSIGNALS_DONT_BREAK_READ -DIGNORE_SIGHUP_SIGQUIT  -DDONT_DECLARE_CXA_PURE_VIRTUAL -L/usr/lib/mysql -lmysqlclient -lz -lm -o /usr/bin/add_word add_word.c
    cp lhd.1.gz /usr/share/man/man1/lhd.1.gz
elif [ "$OS" == "Linux" ]
then
    $cc -I/usr/include/mysql  -DBIG_JOINS=1 -fPIC -L/usr/lib/mysql -lmysqlclient -o lhd lhd.c
    $cc -I/usr/include/mysql  -DBIG_JOINS=1 -fPIC -L/usr/lib/mysql -lmysqlclient -o add_word add_word.c
    cp lhd.1.gz /usr/share/man/man1/lhd.1.gz
fi