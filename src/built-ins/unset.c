/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:01:35 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 15:01:38 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_shell *data, t_env *env)
{
	if (data->env == env && env->next == NULL)
	{
		ft_memdel(data->env->value);
		data->env->value = NULL;
		data->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

static int	unset_next_node(char *key, t_env *env, t_shell *data)
{
	t_env	*tmp;

	while (env && env->next)
	{
		if (ft_strncmp(key, env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(data, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	ft_unset(char **a, t_shell *data)
{
	t_env	*env;

	env = data->env;
	if (!a[1])
		return (0);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		if (env->next)
			data->env = env->next;
		else
			data->env = env;
		free_node(data, env);
		return (0);
	}
	return (unset_next_node(a[1], env, data));
}
