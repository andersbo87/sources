#!/bin/sh
deps () {
    file1=$(/usr/bin/make all-depends-list)
    /usr/bin/make config-recursive
    file2=$(/usr/bin/make all-depends-list)
    if [ "$file1" != "$file2" ]
    then
	deps $1
    else
	echo "Configure complete. Fetching required distfiles."
    fi
}

convertsecs() {
    h=`expr $1 / 3600`
    m=`expr $1 % 3600 / 60`
    s=`expr $1 % 60`
    printf "Operasjonen tok %02d timer, %02d minutter og %02d sekunder\n" $h $m $s
}
if [ $(/usr/bin/id -u) != "0" ]
then
    /usr/bin/printf "\033[00;31mMust be run as root.\033[00m\n"
    exit 1
fi

if [ $(/usr/bin/uname) != "FreeBSD" ]
then
    /usr/bin/printf "\033[00;31mThis script only works on FreeBSD. Sorry.\033[00m\n"
    exit 2
fi
START=$(date +%s)
OLDPAGER=$PAGER
PAGER="more -e"
export PAGER
/usr/sbin/freebsd-update fetch install
/usr/sbin/portsnap fetch
/usr/sbin/portsnap update
updates=`/usr/sbin/pkg version | /usr/bin/grep "<" | /usr/bin/wc -l`
i=0
/usr/bin/less /usr/ports/UPDATING
if [ $updates -eq 0 ]
then
    /usr/bin/printf "\033[1mYour installed ports are up-to-date.\033[0m\n"
    PAGER=$OLDPAGER
    export PAGER
    END=$(date +%s)
    DIFF=$(( $END-$START ))
    echo $(convertsecs $DIFF)
    exit 0
elif [ $updates -eq 1 ]
then
    /usr/bin/printf "\n\n\033[1mThere is 1 update available.\033[0m\n"
else
    /usr/bin/printf "\n\n\033[1mThere are $(( $updates )) updates available.\033[0m\n"
fi
for f in `pkg version | grep "<"`
do
    if [ $f != "<" ]
    then
	port=`pkg info $f | grep Origin | cut -c 18-`
        echo $port
    fi
done
/bin/sleep 5
if [ "$1" != "nofetch" ]
then
echo "Configuring ports and dependencies and fetching required files…"
for fetch in `/usr/sbin/pkg version | /usr/bin/grep "<"`
do
    if [ $fetch != "<" ]
    then
	i=$(($i+1))
	port=`/usr/sbin/pkg info $fetch | /usr/bin/grep Origin | /usr/bin/cut -c 18-`
	/usr/bin/printf "\033]0;Fetching distfiles for $port and dependencies ($i of $(( $updates ))) \007"
	/usr/bin/printf "\033[1mFetching distfiles for $port and dependencies ($i of $(( $updates )))…\033[0m\n"
	cd /usr/ports/$port
	/usr/bin/make config-conditional
	#/usr/bin/make config-recursive
	deps
	/usr/bin/make checksum-recursive
	res=$?
	if [ $res != 0 ]
	then
	    PAGER=$OLDPAGER
	    export PAGER
	    END=$(date +%s)
	    DIFF=$(( $END-$START ))
	    echo $(convertsecs $DIFF)
	    exit $res
	fi
    fi
done
fi
i=0
echo "Fetching done. It *should* be safe to disconnect."
echo "Building and installing the new versions. This could take some time…"
for install in `/usr/sbin/pkg version | /usr/bin/grep "<"`
do
    if [ $install != "<" ]
    then
	i=$(($i+1))
	port=`/usr/sbin/pkg info $install | /usr/bin/grep Origin | /usr/bin/cut -c 18-`
	oldversion=`/usr/sbin/pkg info $install | /usr/bin/head -1`
	name=`/usr/sbin/pkg info $install | /usr/bin/grep Name | /usr/bin/cut -c 18-`
	/usr/bin/printf "\033]0;Compiling and installing new $port ($i of $(( $updates ))) \007"
	cd /usr/ports/$port
	/usr/bin/make clean
	/usr/bin/printf  "\033[1mCompiling new version of $port ($i of $(( $updates )))…\033[0m\n"
	/usr/bin/make build
	res1=$?
	if [ $res1 != 0 ]
	then
	    PAGER=$OLDPAGER
	    export PAGER
	    END=$(date +%s)
	    DIFF=$(( $END-$START ))
	    echo $(convertsecs $DIFF)
	    exit $res1
	fi
	/usr/bin/printf "\033[1mInstalling new version of $port… ($i of $(( $updates )))…\033[0m\n"
	/usr/bin/make deinstall install
	res2=$?
	if [ $res2 != 0 ]
	then
	    PAGER=$OLDPAGER
	    export PAGER
	    END=$(date +%s)
	    DIFF=$(( $END-$START ))
	    echo $(convertsecs $DIFF)
	    exit $res2
	fi
	newversion=`/usr/sbin/pkg info $name | /usr/bin/head -1`
	/usr/bin/printf "\033[1mRemoving old package from /usr/ports/packages/All/$oldversion.txz ($i of $(( $updates )))…\033[0m\n"
	/bin/rm -f /usr/ports/packages/All/$oldversion.txz
	/usr/bin/printf "\033[1mCreating and installing package of new version of $port to /usr/ports/packages/All/$newversion.txz ($i of $(( $updates )))…\033[0m\n"
	/usr/bin/printf "\033]0;Creating package of new version of $newversion.txz ($i of $(( $updates ))) \007"
	/usr/bin/make package
	/usr/bin/printf "\033[1mRunning /usr/bin/make clean in /usr/ports/$port ($i of $(( $updates )))…\033[0m\n"
	/usr/bin/printf "\033]0;Making clean in /usr/ports/$port ($i of $(( $updates ))) \007"
	/usr/bin/make clean
    fi
done

PAGER=$OLDPAGER
export PAGER
#END=$(date +%H%M%S)
END=$(date +%s)
DIFF=$(( $END-$START ))
echo $(convertsecs $DIFF)

