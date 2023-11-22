#!/bin/bash
numFiles=`ls | wc -l`
count=0
while test $count -lt $numFiles
do
	count=`expr $count + 1`
	echo He encontrado $count fichero/s
done
