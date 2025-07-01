/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:32:23 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/01 14:32:25 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_execute(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	if (!current || current->token_type == T_PIPE
		|| current->token_type == T_REDIRECT_IN
		|| current->token_type == T_REDIRECT_OUT
		|| current->token_type == T_APPEND || current->token_type == T_HEREDOC)
		return (0);
	while (current)
	{
		next = current->next;
		if ((current->token_type == T_PIPE && (!next
					|| next->token_type == T_PIPE))
			|| ((current->token_type == T_REDIRECT_IN
					|| current->token_type == T_REDIRECT_OUT
					|| current->token_type == T_APPEND
					|| current->token_type == T_HEREDOC) && (!next
					|| (next->token_type != T_ARGV
						&& next->token_type != T_COMMAND))))
			return (0);
		if (!current->next && (current->token_type == T_PIPE
				|| current->token_type == T_REDIRECT_IN
				|| current->token_type == T_REDIRECT_OUT
				|| current->token_type == T_APPEND
				|| current->token_type == T_HEREDOC))
			return (0);
		current = current->next;
	}
	return (1);
}

void	parser(t_command **commands, t_token *tokens)
{
	int			added;
	t_command	*command;

	command = NULL;
	if (!tokens || !can_execute(tokens))
		return ;
	command = create_command();
	while (tokens)
	{
		if (tokens->token_type == T_COMMAND || tokens->token_type == T_ARGV
			|| tokens->token_type == T_FLAG)
			add_args_command(command, tokens->value);
		else
			update_command(command, tokens);
		if (tokens->token_type == T_PIPE)
		{
			add_command_list(commands, command);
			command = create_command();
			if (!command)
				free_command_list(*commands);
			added = 1;
		}
		else
			added = 0;
		tokens = tokens->next;
	}
	if (command && !added)
		add_command_list(commands, command);
}
