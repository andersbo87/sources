operativsystem=`uname`
if [ "$operativsystem" == "Darwin" ]
then
    ipaddress=`curl -s checkip.dyndns.org|cut -d ":" -f2|cut -d "<" -f1`
    results=`tput colors`
    if [ $results != -1 ]
    then
	PS1='${debian_chroot:+($debian_chroot)}[\[\033[00;32m\]\u@\h\[\033[00m\]:\[\
\033[00;34m\] \W\[\033[00m\]]$ '
	alias ls="ls -FGHi"
    else
	PS1='${debian_chroot:+($debian_chroot)}[\u@\h: \W]\$ '
	alias ls="ls -i"
    fi
    if [ -x /opt/local/bin/fortune ]
    then
	if [ -x /usr/games/fortune ]
	then
	    /usr/games/fortune freebsd-tips
	fi
    fi
    if [ "$ipaddress" == "" ]
    then
	echo "You were logged in `date` on `tty`."
	echo "You are not connected to the Internet."
    else
	echo "You were logged in `date` from IP $ipaddress on `tty`."
    fi
    if [ -f /usr/local/etc/bash_completion ]; then
        . /usr/local/etc/bash_completion
    elif [ -f /opt/local/etc/profile.d/bash_completion.sh ]; then
        . /opt/local/etc/profile.d/bash_completion.sh
    fi
    SERVICE='Terminal'
    if ! ps ax | grep -v grep | grep $SERVICE > /dev/null
    then
        echo "$SERVICE is not running. :("
	case "$TERM" in
	    xterm*|rxvt*)
		PROMPT_COMMAND='echo -ne "\033]0;${USER}: ${HOSTNAME}:`basename \`pwd\``\007"'
		
    # Show the currently running command in the terminal title:
		show_command_in_title_bar()
		{
		    case "$BASH_COMMAND" in
			*\033]0*)
                # The command is trying to set the title bar as well;
                # this is most likely the execution of $PROMPT_COMMAND.
                # In any case nested escapes confuse the terminal, so don't
                # output them.
		;;
            *)
		echo -ne "\033]0;${USER}: ${BASH_COMMAND} - ${HOSTNAME}:`basename \`pwd\`` \007"
		;;
	esac
	}
	trap show_command_in_title_bar DEBUG
	;;
	*)
#    PROMPT_COMMAND='echo -ne "\033]0;${HOSTNAME}:${PWD/$HOME/~} ${USER}\007"'
#    # Show the currently running command in the terminal title:
#    show_command_in_title_bar()
#    {
#        case "$BASH_COMMAND" in
#            *\033]0*)
#                # The command is trying to set the title bar as well;
#                # this is most likely the execution of $PROMPT_COMMAND.
#                # In any case nested escapes confuse the terminal, so don't
#                # output them.
#                ;;
#            *)
#                echo -ne "\033]0;${BASH_COMMAND} - ${HOSTNAME}:${PWD/$HOME/~} ${USER} \007"
#                ;;
#        esac
#    }
#    trap show_command_in_title_bar DEBUG
#    ;;
	esac
    fi
    #export LC_ALL="C"
    export LC_ALL="no_NO.UTF-8"
    export LANG="no_NO.UTF-8"
elif [ "$operativsystem" == "FreeBSD" ]
then
	# $FreeBSD: src/share/skel/dot.profile,v 1.21 2002/07/07 00:00:54 mp Exp $
#
# .profile - Bourne Shell startup script for login shells
#
# see also sh(1), environ(7).
#
# remove /usr/games and /usr/X11R6/bin if you want
    PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/games:$HOME/bin:/usr/local/sbin:/usr/local/bin:/usr/local/kde4/bin:/usr/local/kde4/sbin; export PATH
    
# Setting TERM is normally done through /etc/ttys.  Do only override
# if you're sure that you'll never log in via telnet or xterm or a
# serial line.
# Use cons25l1 for iso-* fonts
# TERM=cons25; 	export TERM
    
    
# set ENV to a file invoked each time sh is started for interactive use.
    ENV=$HOME/.shrc; export ENV
    PAGER="less -M"; export PAGER
#echo "Output of uname -a (for problem reporting):" 
#echo "`uname -a`"
    alias sudo="sudo -E "
#alias su="su -"
    export FTP_PASSIVE_MODE=1
    export LANG="en_US.ISO8859-15"
    export LC_MONETARY="en_US.ISO8859-15"
    export MM_CHARSET="iso8859-15"
#enable colors if the terminal type supports it:
    results=`tput colors`
    if [ $results != -1 ]
    then
	PS1='${debian_chroot:+($debian_chroot)}[\[\033[00;32m\]\u@\h\[\033[00m\]:\[\033[00;34m\] \W\[\033[00m\]]$ '
	alias ls="ls -FGHi"
    else
	PS1='${debian_chroot:+($debian_chroot)}[\u@\h: \W]\$ '
	alias ls="ls -i"
    fi
#[ -x /usr/games/fortune ] && /usr/games/fortune freebsd-tips
    if [[ -n $TERM ]]
    then
	if [[ -n $SSH_CLIENT ]]
	then
	    touch $HOME/innloggingslogg_tmp.txt
            SSH_IP=`echo $SSH_CLIENT | cut -f 1 -d ' '`
            ./user_login.sh &> $HOME/innloggingslogg_tmp.txt
            cat $HOME/innloggingslogg_tmp.txt >> innloggingslogg.txt
            rm $HOME/innloggingslogg_tmp.txt
            echo "Login via SSH $(date +"%A %d. %B %Y") from IP $SSH_IP"
	else
        #ipaddress=`curl -s checkip.dyndns.org|cut -d ":" -f2|cut -d "<" -f1`
        #if [ "$ipaddress" == "" ]
        #then
            echo "You were logged in `date` on `tty`."
             #echo "You are not connected to the Internet."
        #else
        #     echo "You were logged in `date` on `tty`."
        #fi
	fi
    fi
    if [ -f /usr/local/etc/bash_completion ]; then
        . /usr/local/etc/bash_completion
    else
        [[ $PS1 && -f /usr/local/share/bash-completion/bash_completion.sh ]] && \
	    source /usr/local/share/bash-completion/bash_completion.sh
    fi
    case "$TERM" in
	xterm*|rxvt*)
	    PROMPT_COMMAND='echo -ne "\033]0;${USER}: ${HOSTNAME}:`basename \`pwd\``\007"'
	    
    # Show the currently running command in the terminal title:
	    show_command_in_title_bar()
	    {
		case "$BASH_COMMAND" in
		    *\033]0*)
                # The command is trying to set the title bar as well;
                # this is most likely the execution of $PROMPT_COMMAND.
                # In any case nested escapes confuse the terminal, so don't
                # output them.
            ;;
        *)
            echo -ne "\033]0;${USER}: ${BASH_COMMAND} - ${HOSTNAME}:`basename \`pwd\`` \007"
            ;;
    esac
    }
    trap show_command_in_title_bar DEBUG
    ;;
    *)
#    PROMPT_COMMAND='echo -ne "\033]0;${HOSTNAME}:${PWD/$HOME/~} ${USER}\007"'
#    # Show the currently running command in the terminal title:
#    show_command_in_title_bar()
#    {
#        case "$BASH_COMMAND" in
#            *\033]0*)
#                # The command is trying to set the title bar as well;
#                # this is most likely the execution of $PROMPT_COMMAND.
#                # In any case nested escapes confuse the terminal, so don't
#                # output them.
#                ;;
#            *)
#                echo -ne "\033]0;${BASH_COMMAND} - ${HOSTNAME}:${PWD/$HOME/~} ${USER} \007"
#                ;;
#        esac
#    }
#    trap show_command_in_title_bar DEBUG
#    ;;
    esac
fi
