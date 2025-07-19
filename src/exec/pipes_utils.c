/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:31:00 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/19 20:31:04 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_free_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	close_all_pipes_in_child(int **pipes, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	put_error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}
