#include "minishell.h"

int is_quoted(const char *str)
{
    size_t length;

    length = ft_strlen(str);
    if (!length)
        return (0);
    if ((str[0] == '\'' && str[length - 1] == '\'') || (str[0] == '"' && str[length - 1] == '"'))
        return (1);
    return (0);
}

static char	*strip_quotes(const char *str)
{
	size_t	len = ft_strlen(str);

	if ((str[0] == '\'' && str[len - 1] == '\'') ||
		(str[0] == '"' && str[len - 1] == '"'))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

static void	read_heredoc_loop(int fd, const char *delim, int expand, t_env *env)
{
	char	*line;
	char	*expanded;

	rl_catch_signals = 0;
	signal(SIGINT, SIG_DFL);

	while (1)
	{
		line = readline("Heredoc> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
		{
			expanded = expand_variables(line, env, g_minishell.status);
			write(fd, expanded, ft_strlen(expanded));
			write(fd, "\n", 1);
			free(expanded);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		free(line);
	}
}

int	create_heredoc(const char *delimiter, t_env *env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	*delim_clean = strip_quotes(delimiter);
	int		expand = !is_quoted(delimiter);

	if (pipe(pipefd) == -1 || !delim_clean)
		return (-1);
	g_minishell.context = 2; // heredoc
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		read_heredoc_loop(pipefd[1], delim_clean, expand, env);
		free(delim_clean);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	free(delim_clean);
	g_minishell.context = 0; // vuelve al loop principal
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
	{
		close(pipefd[0]);
		return (-1);
	}
	return (pipefd[0]);
}
