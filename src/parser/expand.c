/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuesta- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:49:32 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/05 16:49:34 by mcuesta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*get_var_value(const char *key, t_env *env, int last_status)
{
	char    *val;

	if (!key)
		return (ft_strdup(""));
	if (ft_strncmp(key, "?", 2) == 0)
		return (ft_itoa(last_status));
	val = get_env_value(env, key);
	return (ft_strdup(val ? val : ""));
}

static char	*extract_and_expand(const char *input, t_env *env, size_t *i, int last_status)
{
	size_t	start = ++(*i);
	size_t	len = 0;
	char	*name;
	char	*val;

	if (!input[start])
		return (ft_strdup("$"));
	if (input[start] == '?')
	{
		(*i)++;
		return (get_var_value("?", env, last_status));
	}
	while (input[start + len] && is_var(input[start + len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	name = ft_substr(input, start, len);
	if (!name)
		return (ft_strdup(""));
	val = get_var_value(name, env, last_status);
	free(name);
	*i += len;
	return (val);
}

char	*expand_variables(const char *input, t_env *env, int last_status)
{
	size_t	i = 0;
	int		in_squote = 0, in_dquote = 0;
	char	*result = ft_strdup("");
	char	tmp[2];

	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (input[i] == '$' && !in_squote &&
				(is_var(input[i + 1]) || input[i + 1] == '?'))
			result = ft_strjoin_free(result, extract_and_expand(input, env, &i, last_status), 3);
		else
		{
			tmp[0] = input[i++];
			tmp[1] = '\0';
			result = ft_strjoin_free(result, ft_strdup(tmp), 3);
		}
	}
	return (result);
}
