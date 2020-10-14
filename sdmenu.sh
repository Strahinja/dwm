#!/bin/sh

echo=/usr/bin/echo
command=$($echo -ne "Do nothing\nShutdown\nRestart" | dmenu -p "  Shutdown?")

case $command in
	Shutdown) loginctl poweroff
		  ;;
	Restart)  loginctl reboot
		  ;;
	*)	  ;;
esac

