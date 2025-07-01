/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:17 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 15:00:21 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
// #include "../../include/structs.h"

// void	set_pwd(char *arg, char	*c)
// {
// 	char	*string;
// 	t_shell	env;

// 	string = ft_strjoin(arg, c);
// 	new_env(&env.env, string, NULL);
// 	free (string);
// }

// int	ft_cd(char *arg)
// {
// 	char	c[9999];

// 	t_shell env;
// 	if (arg == NULL)
// 	{
// 		arg = get_env(env.env, "HOME") + 5;
// 		if ((arg - 5) == NULL)
// 		{
// 			printf("cd: HOME not set\n");
// 			return (1);
// 		}
// 	}
// 	getcwd(c, sizeof(c));
// 	if (chdir(arg) == -1)
// 	{
// 		if (arg[0] == '\0')
// 			return (1);
// 		ft_putstr_fd("cd: ", 2);
// 		ft_putstr_fd(arg, 2);
// 		ft_putendl_fd(": No such file or directory", 2);
// 		return (1);
// 	}
// 	set_pwd("OLDPWD=", c);
// 	getcwd(c, sizeof(c));
// 	set_pwd("PWD=", c);
// 	return (0);
// }
