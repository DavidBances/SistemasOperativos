#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void handler(int signum)
{
    time_t current_time;
    struct tm *time_info;

    time(&current_time);
    time_info = localtime(&current_time);

    printf("Hora actual: %02d:%02d:%02d\n", time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

    // Configura una nueva alarma para dentro de 10 segundos
    alarm(10);
}

int main()
{
    // Configura el manejador de señales para SIGALRM
    signal(SIGALRM, handler);

    // Configura la primera alarma para dentro de 10 segundos
    alarm(1);

    while (1)
    {
        // El programa continuará en un bucle infinito
        // Esperando señales SIGALRM
        pause();
    }

    return 0;
}
