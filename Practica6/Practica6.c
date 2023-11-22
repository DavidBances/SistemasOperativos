#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define M 5.0 // Duración de la tarea del proceso padre
#define N 7.0 // Duración de la tarea del proceso padre

volatile int child_ready = 0;

void alarm_handler(int signum)
{
    child_ready = 1;
}

int main(void)
{
    int x, i = 0;
    pid_t pid;

    signal(SIGALRM, alarm_handler); // Configura el manejador de la señal SIGALRM

    pid = fork();
    if (pid == -1)
    {
        perror("Error en la llamada a fork()");
        exit(0);
    }
    else if (pid == 0)
    { // Proceso hijo
        while (1)
        {
            srand(getpid());
            x = 1 + (int)(N * rand() / RAND_MAX + 1.0);
            /* X es un número aleatorio entre 1 y N */
            printf("COMIENZO TAREA HIJO %d\n", i);
            sleep(x);
            printf("FIN TAREA HIJO %d\n", i);
            i++;
            kill(getppid(), SIGALRM); // Envía una señal SIGALRM al padre cuando termine su tarea
            pause();                  // Espera a la señal del padre
        }
    }
    else
    { // Proceso padre
        while (1)
        {
            if (child_ready)
            {
                srand(getpid());
                x = 1 + (int)(M * rand() / RAND_MAX + 1.0);
                /* X es un número aleatorio entre 1 y M */
                printf("COMIENZO TAREA PADRE %d\n", i);
                sleep(x);
                printf("FIN TAREA PADRE %d\n", i);
                i++;
                kill(pid, SIGALRM); // Envía una señal SIGALRM al hijo cuando termine su tarea
                pause();            // Espera a la señal del hijo
            }
        }
    }

    return 0;
}
