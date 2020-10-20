#!/bin/sh

echo=/usr/bin/echo
command=$($echo -ne "Do nothing\nShutdown\nRestart" | dmenu -p "  Shutdown?")

shutdown=$([ -f /usr/sbin/loginctl ] && $echo "loginctl poweroff" \
    || $echo "/sbin/shutdown -h now")
restart=$([ -f /usr/sbin/loginctl ] && $echo "loginctl reboot" \
    || $echo "/sbin/shutdown -r now")

case $command in
	Shutdown) $shutdown
		  ;;
	Restart)  $restart
		  ;;
	*)	  ;;
esac

