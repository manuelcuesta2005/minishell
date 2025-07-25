/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:57:03 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/19 19:57:05 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**create_pipes(int cmd_count)
{
	int	**pipes;
	int	i;
	int	j;

	i = 0;
	pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipes)
		return (NULL);
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			j = 0;
			while (j < i)
			{
				free(pipes[j]);
				j++;
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	execute_child(t_exec_child_args *args)
{
	char	*full_path;
	char	**env_array;

	if (args->index > 0 && dup2(args->pipes[args->index - 1][0],
		STDIN_FILENO) == -1)
		perror("dup2");
	if (args->index < args->cmd_count - 1 && dup2(args->pipes[args->index][1],
		STDOUT_FILENO) == -1)
		perror("dup2");
	close_all_pipes_in_child(args->pipes, args->cmd_count - 1);
	if (apply_redirs(args->cmd) == -1)
		exit(1);
	if (is_command(args->cmd->argv[0]))
		exit(exec_builtin(args->shell, args->cmd));
	full_path = find_executable(args->cmd->argv[0], args->shell->env);
	if (!full_path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	env_array = env_list_to_array(args->shell->env);
	execve(full_path, args->cmd->argv, env_array);
	perror("execve");
	exit(126);
}

static int	fork_and_execute_all(t_shell *shell, t_command *cmd, int **pipes,
		int cmd_count)
{
	pid_t				pid;
	int					i;
	t_exec_child_args	args;

	i = 0;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			return (put_error(), 1);
		if (pid == 0)
		{
			args.shell = shell;
			args.cmd = cmd;
			args.pipes = pipes;
			args.index = i;
			args.cmd_count = cmd_count;
			execute_child(&args);
		}
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int	executor_with_pipes(t_shell *shell)
{
	int			cmd_count;
	int			**pipes;
	t_command	*cmd;
	int			i;
	int			status;

	cmd_count = count_commands(shell->commands);
	pipes = create_pipes(cmd_count);
	cmd = shell->commands;
	i = 0;
	if (!pipes)
		return (perror("malloc"), 1);
	if (fork_and_execute_all(shell, cmd, pipes, cmd_count) != 0)
	{
		close_and_free_pipes(pipes, cmd_count - 1);
		return (1);
	}
	close_and_free_pipes(pipes, cmd_count - 1);
	while (i < cmd_count)
	{
		wait(&status);
		i++;
	}
	if (WIFEXITED(status))
		shell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->status = 128 + WTERMSIG(status);
	return (0);
}
