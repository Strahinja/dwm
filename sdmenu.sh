#!/bin/sh

echo=/usr/bin/echo
command=$($echo -ne "Do nothing\nShutdown\nRestart" | dmenu -p "  Shutdown?")

shutdown=$([ -f /sbin/shutdown ] && $echo "/sbin/shutdown -h now" \
    || $echo "loginctl poweroff")
restart=$([ -f /sbin/shutdown ] && $echo "/sbin/shutdown -r now" \
    || $echo "loginctl reboot")

case $command in
	Shutdown) $shutdown
		  ;;
	Restart)  $restart
		  ;;
	*)	  ;;
esac

