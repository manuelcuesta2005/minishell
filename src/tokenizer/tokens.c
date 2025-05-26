#include "minishell.h"

t_token    *create_token(char *token, t_token_type token_type)
{
    t_token *new_token;

    new_token = (t_token *) malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->value = ft_strdup(token);
    new_token->token_type = token_type;
    new_token->next = NULL;
    return (new_token);
}

t_token_type	get_token_type(char *token)
{
	if (is_command(token))
        return T_COMMAND;
    if (token[0] == '-' && token[1] != '\0' && token[1] != '-')
        return T_FLAG;
    if (is_redirect_in(token))
        return T_REDIRECT_IN;
    if (is_redirect_out(token))
        return T_REDIRECT_OUT;
    if (ft_strncmp(token, "|", 1) == 0)
        return T_PIPE;
    return T_ARGV;
}

void	token_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_token	*tokenize_input(char *input)
{
	char			*copy;
	char			*token;
	t_token			*tokens = NULL;
	t_token			*input_tokenizer;
	t_token_type	type;

	copy = ft_strdup(input);
	token = strtok(copy, " ");
	while (token)
	{
		type = get_token_type(token);
		input_tokenizer = create_token(token, type);
		token_lstadd_back(&tokens, input_tokenizer);
		token = strtok(NULL, " ");
	}
	free(copy);
	return (tokens);
}