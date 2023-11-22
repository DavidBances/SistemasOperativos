#!/bin/bash
function cuadrado()
{
	result=`expr $1 \* $1`
	echo $result
}

echo Por favor, introduce un número
read num
num2=`cuadrado $num`
echo El cuadrado de $num es $num2
