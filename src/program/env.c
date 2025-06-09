#include "minishell.h"

char *get_key(char *env)
{
    int		i;
    char	*set_key;

    i = 0;
    while (env[i] && env[i] != '=')
		i++;
	set_key = malloc(i + 1);
	if (!set_key)
		return (NULL);
	ft_strlcpy(set_key, env, i + 1);
    return(set_key);
}

char *get_value(char *env)
{
	int		i;
	char	*set_value;

	i = 0;
	while(env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (NULL);
	set_value = ft_strdup(env + i + 1);
	return (set_value);
}

void	new_env(t_env **env, char *key, char *value)
{
	t_env	*new;
	t_env	*temporal;

	new = (t_env *) malloc(sizeof(t_env));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (!(*env))
		*env = new;
	else
	{
		temporal = *env;
		while (temporal->next)
		temporal = temporal->next;
		temporal->next = new;
	}
}

void    get_variables(t_env **env, char **envp)
{
    int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (key && value)
		{
			new_env(env, key, value);
			free(key);
			free(value);
		}
		else
		{
			free(key);
			free(value);
		}
		i++;
	}
}
