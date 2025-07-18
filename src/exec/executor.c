/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:33:54 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 17:50:32 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	put_error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

static int	apply_redirs(t_command *command)
{
	if (command->heredoc != -1 && !command->pipe)
	{
		if (dup2(command->heredoc, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(command->heredoc);
			return (-1);
		}
		close(command->heredoc);
	}
	if (command->infile && redirect_input(command->infile) == -1)
		return (-1);
	if (command->outfile && redirect_output(command->outfile) == -1)
		return (-1);
	if (command->append && redirect_output_append(command->append) == -1)
		return (-1);
	return (0);
}

int	count_commands(t_command *commands)
{
	int	count;

	count = 0;
	while (commands)
	{
		count++;
		commands = commands->next;
	}
	return (count);
}

static char	*find_executable(char *command, t_env *envp)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path_env = filter_path(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, command, 1);
		if (access(full_path, X_OK) == 0)
			return (ft_free_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}

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

static void	close_and_free_pipes(int **pipes, int count)
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

static void	close_all_pipes_in_child(int **pipes, int count)
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
		wait(NULL);
		i++;
	}
	return (0);
}

char	*filter_path(t_env *envp, char *key)
{
	size_t	length;

	if (!envp || !key)
		return (NULL);
	length = ft_strlen(key);
	while (envp)
	{
		if (envp->key && ft_strncmp(envp->key, key, length) == 0)
			return (ft_strdup(envp->value));
		envp = envp->next;
	}
	return (NULL);
}

int	only_execute(t_shell *shell, t_command *command, t_env *envp)
{
	pid_t	pid;
	int		status;
	char	*full_path;
	char	**env_array;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	else if (pid == 0)
	{
		if (apply_redirs(command) == -1)
			exit(1);
		if (is_command(command->argv[0]))
			exit(exec_builtin(shell, command));
		full_path = find_executable(command->argv[0], envp);
		if (!full_path)
		{
			ft_putstr_fd("minishell: command not found\n", 2);
			exit(127);
		}
		env_array = env_list_to_array(envp);
		execve(full_path, command->argv, env_array);
		perror("execve");
		ft_free_array(env_array);
		free(full_path);
		exit(126);
	}
	else
		return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}

int	executor(t_shell *shell)
{
	t_command	*command;
	int			save_stdin;
	int			save_stdout;

	if (!shell->commands)
		return (1);
	if (!shell->commands->next)
	{
		command = shell->commands;
		if (is_command(command->argv[0]))
		{
			save_stdin = dup(STDIN_FILENO);
			save_stdout = dup(STDOUT_FILENO);
			apply_redirs(command);
			exec_builtin(shell, command);
			dup2(save_stdin, STDIN_FILENO);
			dup2(save_stdout, STDOUT_FILENO);
			close(save_stdin);
			close(save_stdout);
			return (0);
		}
		else
			return (only_execute(shell, command, shell->env));
	}
	return (executor_with_pipes(shell));
}
