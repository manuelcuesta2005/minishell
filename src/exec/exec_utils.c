#include "minishell.h"

int     exec_builtins(t_shell *shell, char *argv)
{
    if (ft_strncmp(argv, "echo", 4) == 0)
        return (ft_echo(shell, shell->commands));
    else if (ft_strncmp(argv, "env", 3) == 0)
        return (ft_env(shell->env));
    else if (ft_strncmp(argv, "pwd", 3) == 0)
        return (ft_pwd());
    else if (ft_strncmp(argv, "unset", 5) == 0)
        return (1);

    return (0);
}

char    *filter_path(t_env *envp ,char *env_dir)
{
    t_env   *temporal;

    if (!envp)
        return (NULL);
    while (envp)
    {
        if (envp->value && ft_strncmp(envp->value, env_dir, ft_strlen(env_dir)) == 0)
            return (ft_strdup(envp->value));
        envp = envp->next;
    }
    return (NULL);
}

