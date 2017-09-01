#!/bin/sh

# This script requires MPlayer to be installed.
MPlayer=`which mplayer`
if [ "$MPlayer" == "" -o "$MPlayer" == "mplayer: Command not found." ]
then
    echo "MPlayer must be installed."
    exit 1
fi

# If the previous if test passes, let's assume that MPlayer is installed.
mplayer http://lyd.nrk.no/nrk_radio_mp3_mp3_h
