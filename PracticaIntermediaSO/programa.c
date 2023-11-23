#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // Se halla el numero de asistentes.
    int numAsistentesVuelo = atoi(argv[1]);
    // Se crea una matriz con espacio de memoria igual al numero de asistentes de forma dinámica.
    int *asistentes = (int *)malloc(numAsistentesVuelo * sizeof(int));

    // El coordinador crea un proceso hijo que representa al técnico del avión.
    pid_t coordinador = fork();

    // Este es el proceso hijo, es decir, el técnico del avión.
    if (coordinador == 0)
    {
        // Se crea otro proceso hijo que representa al encargado del vuelo.
        pid_t tecnico = fork();

        // Este es el proceso hijo, es decir, el emcargado del vuelo.
        if (tecnico == 0)
        {

            // Este es el proceso padre, es decir, el encargado, aquí se desarrollará el código del mismo
            printf("Soy el encargado del vuelo con pid %d, de padre %d\n", getpid(), getppid());

            // Ahora se crean tantos procesos hijos como se indique en el argumento correspondiente al programa, es decir, el número de asistentes de vuelo.
            for (int i = 0; i < numAsistentesVuelo; i++)
            {
                pid_t asistente = fork();
                // Cada uno de los procesos comprobados aquí son los procesos hijos, es decir, los asistentes de vuelo.
                if (asistente == 0)
                {
                    printf("Soy el asistente de vuelo número: %d, con pid de padre %d\n", i, getpid());
                    alarm(1);
                }
                // En esta parte del código comprobamos que al crear cada uno de los asistentes no hay nungún error.
                else if (asistente < 0)
                {
                    perror("Error en fork.\n");
                    exit(1);
                }
            }
        }
        // En esta parte del código comprobamos que al crear al encargado del vuelo no salte ningún error.
        else if (coordinador < 0)
        {
            perror("Error en fork.\n");
            exit(1);
        }
        // Este es el proceso padre, es decir, el técnico, aquí se desarrollará el código del mismo.
        else
        {
            printf("Soy el técnico del avión, con pid %d, de padre %d.\n", getpid(), getppid());
        }
    }
    // En esta parte del código comprobamos que al crear al técnico del avión no salte ningún error.
    else if (coordinador < 0)
    {
        perror("Error en fork.\n");
        exit(1);
    }
    // Este es el proceso padre, es decir, el coordinador, aquí se desarrollará el código del mismo.
    else
    {
        printf("Soy el Coordinador con pid %d, de padre %d.\n", getpid(), getppid());
    }
    printf("\n");
}