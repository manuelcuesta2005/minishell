/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:26:38 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/18 12:12:38 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	run_minishell(t_shell *shell, t_command *command)
{
	while (1)
	{
		shell->input = readline(INPUT);
		if (!shell->input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (shell->input[0] != '\0')
			add_history(shell->input);
		pre_process(shell);
		shell->tokens = lexer(shell, shell->input);
		shell->commands = NULL;
		parser(&shell->commands, shell->tokens, shell);
		if (shell->commands)
		{
			command = shell->commands;
			executor(shell);
		}
		free(shell->input);
		free_tokens(shell->tokens);
		free_command_list(shell->commands);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*minishell;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	minishell = init_minishell();
	if (!minishell)
		return (1);
	get_variables(&minishell->env, envp);
	init_signals();
	run_minishell(minishell, cmd);
	free_env_list(minishell->env);
	free(minishell);
	return (0);
}
