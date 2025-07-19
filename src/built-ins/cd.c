/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:17 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/19 18:34:02 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

int	change_directory(const char *arg, char *oldpwd)
{
	if (chdir(arg) == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	update_env_vars(t_shell *env, char *cwd, char *oldpwd)
{
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("cd (getcwd after)");
		free(oldpwd);
		return (1);
	}
	set_env(&env->env, "OLDPWD", oldpwd);
	set_env(&env->env, "PWD", cwd);
	free(oldpwd);
	return (0);
}

int	ft_cd(t_shell *env, char **args)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*arg;

	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (env->status = 1);
	}
	arg = get_cd_target(env, args[1]);
	if (!arg)
		return (1);
	if (!get_current_directory(cwd))
		return (1);
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (1);
	if (change_directory(arg, oldpwd))
		return (1);
	return (update_env_vars(env, cwd, oldpwd));
}
