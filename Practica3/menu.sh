#!/bin/bash
while true
do
	echo Por favor, introduce un número entre el 1 y el 3
	read input
	case $input in
		1) echo Has introducido el número $input 
			exit 0;;
		2) echo Has introducido el número $input 
			exit 0;;
		3) echo Has introducido el número $input
			exit 0;;
		*) echo "¡Dije un número entre el 1 y el 3!";;
	esac
done
