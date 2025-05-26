#include "minishell.h"

void print_token_type(t_token_type type)
{
	if (type == T_COMMAND)
		printf("COMMAND");
	else if (type == T_FLAG)
		printf("FLAG");
	else if (type == T_ARGV)
		printf("ARGUMENT");
	else if (type == T_PIPE)
		printf("PIPE");
	else if (type == T_REDIRECT_IN)
		printf("REDIRECT_IN");
	else if (type == T_REDIRECT_OUT)
		printf("REDIRECT_OUT");
	else
		printf("UNKNOWN");
}

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: '%s', Type: ", tokens->value);
		print_token_type(tokens->token_type);
		printf("\n");
		tokens = tokens->next;
	}
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_shell   *minishell;

    minishell = (t_shell *) malloc(sizeof(t_shell));
    if (!minishell)
        return (1);
    get_variables(&minishell->env, envp);
    while (1)
    {
        minishell->input = readline("\033[1;34m⮞ \033[1;36m[minishell]\033[1;34m ⮜ \033[0;32mready$ \033[0m");
        add_history(minishell->input);
        pre_process(minishell);
        ft_printf("%s\n", minishell->input);
        minishell->tokens = tokenize_input(minishell->input);
        print_tokens(minishell->tokens);
        free(minishell->input);
    }
    return (0);
}
