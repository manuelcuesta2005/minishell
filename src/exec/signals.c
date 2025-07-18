/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:34:22 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/03 16:24:00 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_status;

static void	aux_signals(int sig)
{
	if (g_status == 3)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_status = 4;
	}
	(void)sig;
}

static void	handle_signals(int sig)
{
	if (g_status == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_status == 1)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_status = 0;
	}
	else if (g_status == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		ioctl(STDIN_FILENO, TIOCSTI, (char *)"\n");
		exit(1);
	}
	aux_signals(sig);
}

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}
