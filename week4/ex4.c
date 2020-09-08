#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char command[256] = "";
    do
    {
        if (fork())
        {
            char temp; // I need to read \n to continue parsing
            scanf("%256[^\n]", command);
            scanf("%c", &temp);
        }
        else
        {
            // split string by spaces
            size_t spaceCount = 0;
            for (size_t i = 0; i < strlen(command); ++i) // count our delimiters
            {
                if (isspace(command[i]))
                    ++spaceCount;
            }
            char **args = malloc((spaceCount + 2) * sizeof(char *)); // allocate reqired memory dynamically
            for (size_t i = 0; i < spaceCount + 1; i++)
            {
                args[i] = malloc(256 * sizeof(char));
            }

            size_t from = 0, to = 0, currentArg = 0;
            for (size_t i = 0; i < strlen(command) + 1; ++i)
            {
                if (!command[i] || isspace(command[i]))
                {
                    // copy argument between spaces
                    to = i;
                    size_t length = to - from;
                    args[currentArg] = malloc((length + 1) * sizeof(char));
                    strncpy(args[currentArg], &command[from], length);
                    args[currentArg][length] = 0;
                    from = to + 1;
                    ++currentArg;
                }
            }
            args[spaceCount + 1] = NULL;
            // execvpe stuff
            char *path = getenv("PATH");
            char pathenv[strlen(path) + sizeof("PATH=")];
            sprintf(pathenv, "PATH=%s", path);
            char *envp[] = {pathenv, NULL};
            execvpe(args[0], args, envp);

            // no memory leaks
            for (size_t i = 0; i < spaceCount + 1; i++)
            {
                free(args[i]);
            }
            free(args);

            // Hasta la vista, process
            exit(0);
        }
    } while (strcmp(command, "exit")); // exit for exit. Seems obvious.
    return 0;
}