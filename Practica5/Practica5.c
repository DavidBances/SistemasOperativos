#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char *programs[] = {"xload", "xeyes", "xlogo", "xcalc", "xclock", "-update", "1"};
    int num_programs = sizeof(programs) / sizeof(programs[0]);
    pid_t child_pids[num_programs];
    int active_children = num_programs;

    for (int i = 0; i < num_programs; i++)
    {
        pid_t child_pid = fork();
        if (child_pid == 0)
        {
            // Este es el proceso hijo, ejecuta el programa correspondiente.
            if (i == 0)
            {
                execl("/bin/xload", "xload", (char *)NULL);
            }
            if (i == 1)
            {
                execl("/bin/xeyes", "xeyes", (char *)NULL);
            }
            if (i == 2)
            {
                execl("/bin/xlogo", "xlogo", (char *)NULL);
            }
            if (i == 3)
            {
                execl("/bin/xcalc", "xcalc", (char *)NULL);
            }
            if (i == 4)
            {
                execl("/bin/xclock", "xclock", "-update", "1", (char *)NULL);
            }
            // Si execlp falla, muestra un mensaje y sale.
            perror("Error en execlp");
            exit(1);
        }
        else if (child_pid < 0)
        {
            // Error al crear el proceso hijo.
            perror("Error en fork");
            exit(1);
        }
        else
        {
            child_pids[i] = child_pid;
        }

        // Avanza al siguiente programa si hay argumentos adicionales.
        /* if (i < num_programs - 1)
        {
            i++;
        } */
    }

    /*  while (active_children > 0)
     {
         // Espera a que cualquier hijo termine.
         int status;
         pid_t terminated_pid = wait(&status);

         // Encuentra el índice del programa correspondiente al hijo terminado.
         int program_index = -1;
         for (int i = 0; i < num_programs; i++)
         {
             if (terminated_pid == child_pids[i])
             {
                 program_index = i;
                 break;
             }
         }

         if (program_index != -1)
         {
             printf("El programa '%s' ha terminado. No se vuelve a crear.\n", programs[program_index]);
             // Marca el proceso como finalizado.
             child_pids[program_index] = -1;
             active_children--;

             if (active_children == 0)
             {
                 printf("Todos los hijos han terminado. Saliendo del programa.\n");
                 break;
             }
         }
         else
         {
             printf("Un hijo no identificado ha terminado.\n");
         }
     } */

    return 0;
}
