#!/bin/bash
if test $# -eq 0
then
	dir=.
fi


if test $# -eq 1
then
	dir=$1
	if test ! -d $dir
	then
		echo El directorio no es un directorio.
		exit 0;
	fi
	cd $dir
fi


if test $# -gt 1
then
	echo Número de argumentos incorrecto.
	exit 0;
fi
	
count=0
until test $input -eq 10
do
echo Escribe un número entre 1 y 10, para elegir una de las siguientes opciones: 
echo 1\) Numero de archivos.
echo 2\) Numero de subdirectorios. 
echo 3\) Fichero más grande.
echo 4\) Fichero más pequeño.
echo 5\) Espacio total ocupado.
echo 6\) Número de ficheros con permiso de lectura para el usuario que ejecuta el script. 
echo 7\) Número de ficheros con permiso de escritura para el usuario que ejecuta el script. 
echo 8\) Número de ficheros con permiso de ejecucuciónpara el usuario que ejecuta el script. 
echo 9\) Ficheros con permiso de ejecución para todos los usuarios.
echo 10\) Salir.
read input
	case $input in
		1) echo Número de archivos.
			numFiles=`ls | wc -l`
			echo El número de archivos es: $numFiles;;
		
		2) echo Número de subdirectorios.
			for i in $( ls . )
			do
				if test -d $i
				then
					count=`expr $count + 1`
				fi
			done
			echo El número de subdirectorios es: $count.;;
			
		3) echo Fichero más grande.
			max=0
			archivo=""
			for i in $( ls .)
			do
				tam=$(du -b $i | awk '{print $1}')
				if test $tam -gt $max
					then 
					max=$tam
					archivo=$i
				fi
			done
			echo El archivo más grande es: $archivo y ocupa $max b.;;
			
		4) echo Fichero más pequeño.
			min=9999999999999
			archivo=""
			for i in $( ls .)
			do
				tam=$(du -b $i | awk '{print $1}')
				if test $tam -lt $min
					then 
					min=$tam
					archivo=$i
				fi
			done
			echo El archivo más pequeño es: $archivo y ocupa $min b.;;
			
		5) echo Espacio total ocupado.
			tam=$(du -sh .)
			echo El espacio total ocupado en disco por el directorio actual es: $tam.;;
			
		6) echo Número de ficheros con permiso de lectura para el usuario que ejecuta el script.
			num=0
			for i in $( ls .)
			do 
				if test -r $i 
				then
				num=`expr $num + 1`
				fi
			done
			echo El numero de archivos con permiso de lectura es: $num.;;
			
		7) echo Número de ficheros con permiso de escritura para el usuario que ejecuta el script.
			num=0
			for i in $( ls .)
			do 
				if test -w $i 
				then
				num=`expr $num + 1`
				fi
			done
			echo El numero de archivos con permiso de escritura es: $num.;;
			
		8) echo Número de ficheros con permiso de ejecución para el usuario que ejecuta el script.
			num=0
			for i in $( ls .)
			do 
				if test -x $i 
				then
				num=`expr $num + 1`
				fi
			done
			echo El numero de archivos con permiso de ejecución es: $num.;;
			
		9) echo Ficheros con permiso de ejecución para todos los usuarios.
			num=0
			for i in $( ls .)
			do 
				if test -x $i 
				then
				num=`expr $num + 1`
				fi
			done
			echo El numero de archivos con permiso de ejecución para todos los usuarios es: $num.;;
			
		10) echo Has salido del programa.
			exit 0;;
			
		*) echo Escoge una de las opciones dadas.;;
	esac
done
