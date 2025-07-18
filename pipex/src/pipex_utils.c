/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:15:35 by nroson-m          #+#    #+#             */
/*   Updated: 2025/04/21 15:23:23 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	put_error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

char	*search_location(char *comand, char **envp)
{
	char	**locations;
	char	*location;
	int		i;
	char	*temp_location;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	locations = ft_split(envp[i] + 5, ':');
	i = 0;
	while (locations[i])
	{
		temp_location = ft_strjoin(locations[i], "/");
		location = ft_strjoin(temp_location, comand);
		free(temp_location);
		if (access(location, F_OK) == 0)
			return (location);
		free(location);
		i++;
	}
	i = -1;
	while (locations[++i])
		free(locations[i]);
	free(locations);
	return (0);
}

void	exec(char *argv, char **envp)
{
	char	**comand;
	int		i;
	char	*location;

	i = -1;
	comand = ft_split(argv, ' ');
	location = search_location(comand[0], envp);
	if (!location)
	{
		while (comand[++i])
			free(comand[i]);
		free(comand);
		put_error();
	}
	if (execve(location, comand, envp) == -1)
		put_error();
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	fout;

	fout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fout == -1)
		put_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fout, STDOUT_FILENO);
	close(fd[1]);
	exec(argv[3], envp);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int	fin;

	fin = open(argv[1], O_RDONLY, 0777);
	if (fin == -1)
		put_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(fin, STDIN_FILENO);
	close(fd[0]);
	exec(argv[2], envp);
}
