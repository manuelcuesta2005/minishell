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

extern int	g_status;

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
	g_status = 0;
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
		parser(&minishell->commands, minishell->tokens, minishell);
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
