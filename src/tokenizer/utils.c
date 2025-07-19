/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:27:23 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/07 13:38:28 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(char *token)
{
	if (ft_strcmp("echo", token) == 0)
		return (1);
	else if (ft_strcmp("cd", token) == 0)
		return (1);
	else if (ft_strcmp("pwd", token) == 0)
		return (1);
	else if (ft_strcmp("export", token) == 0)
		return (1);
	else if (ft_strcmp("unset", token) == 0)
		return (1);
	else if (ft_strcmp("env", token) == 0)
		return (1);
	else if (ft_strcmp("exit", token) == 0)
		return (1);
	return (0);
}

int	is_redirect(char *input)
{
	if (ft_strcmp(">>", input) == 0)
		return (1);
	else if (ft_strcmp(">", input) == 0)
		return (1);
	else if (ft_strcmp("<<", input) == 0)
		return (1);
	else if (ft_strcmp("<", input) == 0)
		return (1);
	else if (ft_strcmp("|", input) == 0)
		return (1);
	return (0);
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
		if ((arg[i] == '\'' || arg[i] == '"') && quote == 0)
			quote = arg[i++];
		while (quote && arg[i] && arg[i] != quote)
			result[j++] = arg[i++];
		if (quote && arg[i] == quote)
		{
			quote = 0;
			i++;
		}
		while (!quote && arg[i] && arg[i] != '\'' && arg[i] != '"')
			result[j++] = arg[i++];
	}
	result[j] = '\0';
	return (result);
}

int	should_expand(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '$' && !in_single)
			return (1);
		i++;
	}
	return (0);
}

t_token	*create_token(char *token, t_token_type token_type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(token);
	new_token->token_type = token_type;
	new_token->next = NULL;
	return (new_token);
}
