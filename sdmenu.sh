#!/bin/sh

command=$(echo -ne "Do nothing\nShutdown\nRestart" | dmenu -p "  Shutdown?")

case $command in
	Shutdown) loginctl poweroff
		  ;;
	Restart)  loginctl reboot
		  ;;
	*)	  ;;
esac

