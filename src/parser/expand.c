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

char	*get_var_value_simple(const char *key)
{
	char *val = getenv(key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

char	*expand_variables_simple(const char *input)
{
	char	*result = malloc(1);
	size_t	i = 0;
	size_t	len = ft_strlen(input);
	char	*var_name;
	size_t	var_len;

	if (!result)
		return (NULL);
	result[0] = '\0';

	while (i < len)
	{
		if (input[i] == '$' && input[i + 1]
			&& (ft_isalpha(input[i + 1]) || input[i + 1] == '_'))
		{
			i++;
			var_len = 0;
			while (i + var_len < len && (ft_isalnum(input[i + var_len]) || input[i + var_len] == '_'))
				var_len++;
			var_name = strndup(&input[i], var_len);
            char *var_value = get_var_value_simple(var_name);
			result = ft_strjoin_free(result, var_value, 3);
			free(var_name);
			i += var_len;
		}
		else
		{
			char tmp[2] = {input[i++], '\0'};
			result = ft_strjoin_free(result, ft_strdup(tmp), 3);
		}
	}
	return (result);
}
