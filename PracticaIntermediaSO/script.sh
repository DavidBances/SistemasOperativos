#!/bin/bash
constanteQueEsIgualA1=1
while true
do 
    echo -e "Elije una de las siguientes opciones: \n1- Mostrar código del programa. \n2- Compilar programa. \n3- Ejecutar programa. \n4- Salir."
    read opcionElejida

    case $opcionElejida in

        1) #Si la opción elegida es 1, muestra el codigo del programa. 
            echo ""
            cat programa.c 
            echo -e "\n"
           ;;
    
        2) #Si la opción elegida es 2, compila el programa.
            echo ""
            gcc programa.c -o programa
            echo -e "\n" 
            ;;
        3) #Si la opción elegida es 3 y tiene permisos de ejecucion, ejecuta el programa.
            echo ""
            if test -x programa
            then
                until test $asistentesDeVuelo -ge $constanteQueEsIgualA1
                do
                    echo Escribe el número de asistentes de vuelo del avión:
                    read asistentesDeVuelo
                done
                ./programa $asistentesDeVuelo 
            else  
                echo Permiso denegado.
            fi 
            echo -e "\n"
            ;;
        4)  #Si la opción elegida es 4, se sale del script.
            echo ""
            echo Saliendo...
            exit 0;;
        *) 
            echo ""
            echo ¡Dije un número entre el 1 y el tres!
            echo -e "\n"
            ;;
        esac
done