#include "../include/minishell.h"

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell>");
        if (!line)
        {
            write(1, "\n", 1);
            break;
        }
        free(line);
        
    }
    
}