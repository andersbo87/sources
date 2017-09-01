#!/bin/sh

# A small shell script that locks the GNOME 3 screen.
dbus-send --type=method_call --dest=org.gnome.ScreenSaver /org/gnome/ScreenSaver org.gnome.ScreenSaver.Lock
