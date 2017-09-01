#!/bin/sh
if [ $(id -u) != 0 ]; then
    echo "You must be root to continue."
    exit 1
fi
# Disable tapping with touchpad (in reality, disable the whole touchpad)
#sudo killall -USR1 moused
res1=`less /var/run/dmesg.boot | grep ums0 | head -2 | tail -1`
res2=`less /var/run/dmesg.boot | grep ums1 | head -2 | tail -1`
if [ "$res1" == "ums0: 2 buttons and [XY] coordinates ID=2" ]
then
    kill -USR1 `ps ax | grep /usr/sbin/moused | grep ums0 | xargs | cut -d ' ' -f 1`
    exit 0
fi

if [ "$res2" == "ums1: 2 buttons and [XY] coordinates ID=2" ]
then
    kill -USR1 `ps ax | grep /usr/sbin/moused | grep ums1 | xargs | cut -d ' ' -f 1`
    exit 0
fi
echo $res1
echo $res2
echo "Disabling moused on the USB didn't seem to work…"
exit 1
