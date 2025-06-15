#include "minishell.h"

int only_execute(t_command *command, t_env *envp)
{
    pid_t   pid;

    if (pid == -1)
        return (perror("fork"), 1);
    
}
