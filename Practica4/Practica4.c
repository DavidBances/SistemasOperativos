#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    char *directorio;

    if (argc == 0)
    {
        directorio = "/home/david/Sistemas Operativos";
    }
    else if (argc = 1)
    {
        if (chdir(argv[0]) != 0)
        {
            perror("Error al cambiar el directorio");
            exit;
        }
        directorio = argv[0];
    }
    else
    {
        perror("Ha introducido más argumentos de los deseados.");
        exit;
    }
    return 0;
}