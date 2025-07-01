#include "minishell.h"

int     exec_builtin_child(t_shell *shell, t_command *command)
{
    char    *name_command;

    name_command = command->argv[0];
    if (!name_command)
        return (0);
    // if (ft_strncmp(name_command, "echo", 4) == 0)
    //     return (ft_echo(shell, command));
    else if (ft_strncmp(name_command, "env", 3) == 0)
        return (ft_env(shell->env));
    else if (ft_strncmp(name_command, "pwd", 3) == 0)
        return (ft_pwd());
    return (-1);
}

char    *ft_strjoin_free(char *s1, char *s2, int mode)
{
    char    *result;
    size_t  len1;
    size_t  len2;
    size_t  i;
    size_t  j;

    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = malloc(len1 + len2 + 1);
    if (!result)
        return (NULL);
    while (i++ < len1)
        result[i] = s1[i];
    while (j < len2)
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';
    if (mode == 1 || mode == 3)
        free(s1);
    if (mode == 2 || mode == 3)
        free(s2);
    return (result);
}

char    **env_list_to_array(t_env *envp)
{
    t_env   *temporal;
    char    **env_array;
    char    *env_line;
    int     count;
    int     i;

    temporal = envp;
    count = 0;
    i = 0;
    while (temporal)
    {
        if (temporal->key && temporal->value)
            count++;
        temporal = temporal->next;
    }
    env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return (NULL);
    temporal = envp;
    while (temporal)
    {
        if (temporal->key && temporal->value)
        {
            env_line = ft_strjoin(temporal->key, "=");
            env_array[i] = ft_strjoin_free(env_line, temporal->value, 1);
            i++;
        }
        temporal = temporal->next;
    }
    env_array[i] = NULL;
    return (env_array);
}

void    ft_free_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
