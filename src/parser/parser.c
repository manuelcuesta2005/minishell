/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:32:23 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/19 17:10:45 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	can_execute(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	if (!current || current->token_type == T_PIPE)
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

void	parser(t_command **commands, t_token *tokens, t_shell *shell)
{
	int				added;
	t_command		*command;
	t_token_type	prev_type;

	prev_type = -1;
	command = NULL;
	if (!tokens || !can_execute(tokens))
		return ;
	command = create_command();
	while (tokens)
	{
		if (tokens->token_type == T_COMMAND || tokens->token_type == T_ARGV
			|| tokens->token_type == T_FLAG)
		{
			if (prev_type != T_REDIRECT_IN && prev_type != T_REDIRECT_OUT
				&& prev_type != T_APPEND && prev_type != T_HEREDOC)
				add_args_command(command, tokens->value);
		}
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
		else if (tokens->token_type == T_HEREDOC)
		{
			int	fd = create_heredoc(tokens->next->value, shell);
			if (fd == -1)
				return ;
			command->heredoc = fd;
		}
		else
			added = 0;
		prev_type = tokens->token_type;
		tokens = tokens->next;
	}
	if (command && !added)
		add_command_list(commands, command);
	else
		free_command(command);
}
