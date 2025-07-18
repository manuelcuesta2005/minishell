/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:15:35 by nroson-m          #+#    #+#             */
/*   Updated: 2024/10/01 11:40:38 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pidchild;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			put_error();
		pidchild = fork();
		if (pidchild == -1)
			put_error();
		if (pidchild == 0)
			child_process(argv, envp, fd);
		waitpid(pidchild, NULL, 0);
		parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("mal numero de argumentos", 2);
		ft_putstr_fd("Ejecutalo asi: ar1 cmd1 cmd2 ar2", 1);
	}
	return (0);
}
