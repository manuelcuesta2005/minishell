/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:26:38 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:26:42 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	print_command(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("=== Comando ===\n");
		// Mostrar argumentos
		if (cmd->argv)
		{
			printf("argv:\n");
			while (cmd->argv[i])
			{
				printf("  [%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
			i = 0;
		}
		else
			printf("argv: NULL\n");
		// Mostrar redirecciones y heredoc
		printf("infile:  %s\n", cmd->infile ? cmd->infile : "NULL");
		printf("outfile: %s\n", cmd->outfile ? cmd->outfile : "NULL");
		printf("heredoc: %s\n", cmd->heredoc ? cmd->heredoc : "NULL");
		printf("append:  %s\n", cmd->append ? cmd->append : "NULL");
		// Mostrar si hay pipe
		printf("pipe:    %d\n", cmd->pipe);
		printf("=============\n\n");
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*minishell;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	minishell = init_minishell();
	if (!minishell)
		return (1);
	get_variables(&minishell->env, envp);
	init_signals();
	while (1)
	{
		minishell->input = readline("\033[1;34m⮞ \033[1;36m[minishell]\033[1;34m ⮜ \033[0;32mready$ \033[0m");
		if (!minishell->input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (minishell->input[0] != '\0')
			add_history(minishell->input);
		pre_process(minishell);
		minishell->tokens = lexer(minishell->input);
		minishell->commands = NULL;
		parser(&minishell->commands, minishell->tokens);
		print_command(minishell->commands);
		if (minishell->commands)
		{
			cmd = minishell->commands;
			while (cmd)
			{
				clean_arguments(cmd);
				cmd = cmd->next;
			}
			executor(minishell);
		}
		free(minishell->input);
		free_tokens(minishell->tokens);
		free_command_list(minishell->commands);
	}
	free_env_list(minishell->env);
	free(minishell);
	return (0);
}
