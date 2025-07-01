/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:59 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 15:01:00 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"
// #include "../../include/structs.h"

// long long	ft_atoll(const char *nptr)
// {
// 	long long	num;
// 	int			sign;
// 	int			i;

// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
// 		nptr++;
// 	if (nptr[i] == '-')
// 		sign = sign * -1;
// 	if (nptr[i] == '+' || nptr[i] == '-')
// 		nptr++;
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		num = (num * 10) + nptr[i] - '0';
// 		nptr++;
// 	}
// 	return (num * sign);
// }
// int	ms_check_exit_arg(char *arg)
// {
// 	int			i;
// 	long long	exit_code;

// 	i = 0;
// 	while (arg[i] == ' ')
// 		i++;
// 	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
// 		i++;
// 	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n", arg);
// 		t_shell.exit = 255;
// 		return (1);
// 	}
// 	exit_code = ft_atoll(arg);
// 	t_shell.exit = exit_code % 256;
// 	if (t_shell.exit < 0 || t_shell.exit > 255)
// 		t_shell.exit = 255;
// 	return (0);
// }

// void	ms_exit(char **arg, t_job *job)
// {
// 	int	i;

// 	i = 0;
// 	printf("exit\n");
// 	if (arg[0])
// 	{
// 		i = ms_check_exit_arg(arg[0]);
// 		if (arg[1] && i == 0)
// 		{
// 			printf("minishell: exit: too many arguments\n");
// 			t_shell.exit = 1;
// 			return ;
// 		}
// 	}
// 	free_exit(job);
// 	exit(t_shell.exit);
// }
