#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int calculaAleatorios(int min, int max);
void Tecnico(int sig);
void Encargado(int sig);
void Asistentes(int sig);
int crearAsistentes(int numAsistentesVuelo, int *asistentes, struct sigaction ss);

int main(int argc, char *argv[])
{
    // Se halla el numero de asistentes.
    int numAsistentesVuelo = atoi(argv[1]);
    // Se crea una matriz con espacio de memoria igual al numero de asistentes de forma dinámica.
    int *asistentes = (int *)malloc(numAsistentesVuelo * sizeof(int));
    int estadoEncargado, estadoTecnico, salidaEncargado, salidaTecnico, numPasajeros;
    struct sigaction ss;

    printf("COMIENZA EL VUELO:\n");

    // Se crea otro proceso hijo que representa al técnico del vuelo.
    pid_t tecnico = fork();

    // En esta parte del código comprobamos que al crear al técnico del vuelo no salte ningún error.
    if (tecnico == -1)
    {
        perror("Error en fork.\n");
        exit(1);
    }

    // Aquí se desarrolla el código del técnico.
    else if (tecnico == 0)
    {
        sigemptyset(&ss.sa_mask);
        ss.sa_flags = 0;
        ss.sa_handler = Tecnico;

        if (-1 == sigaction(SIGUSR1, &ss, NULL))
        {
            perror("Error en la llamada.");
            return -1;
        }
        pause();
    }

    // Se crea otro proceso hijo que representa al encargado del vuelo.
    pid_t encargado = fork();

    // En esta parte del código comprobamos que al crear al encargado del vuelo no salte ningún error.
    if (encargado == -1)
    {
        perror("Error en el fork.\n");
        exit(1);
    }
    // Aquí se desarrolla el código del encargado.
    else if (encargado == 0)
    {
        sigemptyset(&ss.sa_mask);
        ss.sa_flags = 0;
        ss.sa_handler = Encargado;

        if (-1 == sigaction(SIGUSR1, &ss, NULL))
        {
            perror("Error en la llamada.");
            return -1;
        }
        pause();
    }

    sleep(2);
    kill(tecnico, SIGUSR1);
    wait(&estadoTecnico);
    salidaTecnico = WEXITSTATUS(estadoTecnico);

    if (salidaTecnico == 1)
    {
        // El técnico confirma que el vuelo es viable.
        printf("El tecnico del avion confirma que el vuelo es viable y por tanto manda una señal al coordinador.\n");
        printf("El coordinador, una vez confirmada la viabilidad del despegue, pide al encargado comprobar el número de asientos.\n");
        kill(encargado, SIGUSR1);

        wait(&estadoEncargado);
        salidaEncargado = WEXITSTATUS(estadoEncargado);

        if (salidaEncargado == 1)
        {
            // Este código indica que el vuelo presenta overbucking.            printf("El encargado del avion confirma que hay overbucking y avisa al coordinador.\n");
            numPasajeros = crearAsistentes(numAsistentesVuelo, asistentes, ss);

            printf("Debido al overbucking que se da en el avión no se pudieron subir 10 de los pasajeros.\n");
            numPasajeros = numPasajeros - 10;
        }
        else
        {
            // Este código indica que el vuelo no presenta overbucking.
            printf("El encargado del avion confirma que no hay overbucking y por lo tanto avisa al coordinador que todos los pasajeros se han podido montar.\n\n");
            numPasajeros = crearAsistentes(numAsistentesVuelo, asistentes, ss);
        }

        printf("El coordinador avisa de que ya han embarcado los %d pasajeros.\n", numPasajeros);
        printf("El avión comienza el despegue.\n");
    }
    else
    {
        // Se indica en este código que el vuelo no es viable y por lo tanto el proceso encargado se termina.
        printf("El tecnico del avion avisa al coordinador de que el vuelo NO es viable.\n");
        printf("Termina el vuelo.\n");
        kill(encargado, SIGKILL);
    }
    return 0;
}

// Calcula un número aleatorio entre un mínimo y un máximo que se proporcionen.
int calculaAleatorios(int min, int max)
{
    srand(getpid());
    return rand() % (max - min + 1) + min;
}

// Se lleva a cabo el trabajo del técnico.
void Tecnico(int sig)
{
    printf("Técnico comprobando si el vuelo %d, es viable...\n", getpid());
    sleep(calculaAleatorios(3, 6));
    exit(calculaAleatorios(0, 1));
}
// Se lleva a cabo el trabajo del encargado.
void Encargado(int sig)
{
    printf("Encargado revisando si hay overbooking...\n");
    sleep(2);
    exit(calculaAleatorios(0, 1));
}

// Se lleva a cabo el trabajo de los asistentes.
void Asistentes(int sig)
{
    printf("Asistentes calculando tiempo de embarque...\n");
    sleep(calculaAleatorios(3, 6));
    exit(calculaAleatorios(20, 30));
}

// Se crean a los asistentes de vuelo y se devuelve el número total de pasajeros del avión.
int crearAsistentes(int numAsistentesVuelo, int *asistentes, struct sigaction ss)
{
    pid_t asistente;
    int estadoAsistente, salidaAsistente;
    int numPasajeros = 0;

    printf("El coordinador pide a los asistentes de vuelo que empiecen a embarcar a todos los pasajeros.\n");

    // Se crean cada uno de los asistentes según el número que se proporciona como parámetro, se quedan esperando a la señal 2.
    for (int i = 0; i < numAsistentesVuelo; i++)
    {
        asistente = fork();

        if (asistente == -1)
        {
            perror("Error en la llamada a fork()");
        }
        else if (asistente == 0)
        {
            sigemptyset(&ss.sa_mask);
            ss.sa_flags = 0;
            ss.sa_handler = Asistentes;

            if (-1 == sigaction(SIGUSR2, &ss, NULL))
            {
                perror("Llamda a señal");
                return -1;
            }

            pause();
        }
        else
        {
            asistentes[i] = asistente;
        }
    }
    sleep(2);

    // Se envía la señal número 2 a cada uno de los asistentes de vuelo para que terminen el proceso.
    for (int i = 0; i < numAsistentesVuelo; i++)
    {
        kill(asistentes[i], SIGUSR2);
    }

    for (int i = 0; i < numAsistentesVuelo; i++)
    {
        wait(&estadoAsistente);
        salidaAsistente = WEXITSTATUS(estadoAsistente);
        printf("El asistente %d ha contado a %d pasajeros\n", asistentes[i], salidaAsistente);
        numPasajeros = numPasajeros + salidaAsistente;
    }

    free(asistentes);
    return numPasajeros;
}