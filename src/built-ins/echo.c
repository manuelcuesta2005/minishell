/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:00:31 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 15:00:33 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	put_lines(int i, char **s, int out)
{
	while (s[i])
	{
		ft_putstr_fd(s[i++], out);
		if (s[i])
			ft_putchar_fd(' ', out);
	}
}

int	ft_echo(t_shell *data, t_command *simple_cmd)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = false;
	(void)data;
	while (simple_cmd->argv[i] && simple_cmd->argv[i][0] == '-'
		&& simple_cmd->argv[i][1] == 'n')
	{
		j = 1;
		while (simple_cmd->argv[i][j] == 'n')
			j++;
		if (simple_cmd->argv[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	put_lines(i, simple_cmd->argv, STDOUT_FILENO);
	if (n_option == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
