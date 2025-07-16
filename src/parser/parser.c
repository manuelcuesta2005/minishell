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


char	*remove_quotes(const char *arg)
{
	char	*result;
	int		i;
	int		j;
	char	quote;
	size_t	len;
	
	if (!arg)
		return (NULL);
	len = ft_strlen(arg);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			quote = arg[i++];
			while (arg[i] && arg[i] != quote)
				result[j++] = arg[i++];
			if (arg[i] == quote)
				i++;
		}
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}

void	clean_arguments(t_command *cmd)
{
	int		i;
	char	*cleaned;

	if (!cmd || !cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i])
	{
		cleaned = remove_quotes(cmd->argv[i]);
		free(cmd->argv[i]);
		cmd->argv[i] = cleaned;
		i++;
	}
}

void	expand_token(t_token *token, t_env *env, int status)
{
	char	*expanded;
	char	*cleaned;
	size_t	len;

	if (!token || !token->value)
		return ;
	len = ft_strlen(token->value);
	if ((token->value[0] == '\'' && token->value[len - 1] == '\''))
	{
		cleaned = remove_quotes(token->value);
		free(token->value);
		token->value = cleaned;
		return ;
	}
	expanded = expand_variables(token->value, env, status);
	if (token->value[0] == '"' && token->value[len - 1] == '"')
	{
		free(token->value);
		token->value = expanded;
		return ;
	}
	cleaned = remove_quotes(expanded);
	free(token->value);
	free(expanded);
	token->value = cleaned;
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
		expand_token(tokens, shell->env, shell->status);
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
			int fd = create_heredoc(tokens->next->value, shell->env);
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
