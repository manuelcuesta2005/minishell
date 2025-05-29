#include "minishell.h"

const char *get_token_type_name(t_token_type type)
{
    switch (type)
    {
        case T_COMMAND:      return "COMMAND";
        case T_ARGV:         return "ARG";
        case T_FLAG:         return "FLAG";
        case T_PIPE:         return "PIPE";
        case T_REDIRECT_IN:  return "REDIRECT_IN";
        case T_REDIRECT_OUT: return "REDIRECT_OUT";
        case T_APPEND:       return "APPEND";
        case T_HEREDOC:      return "HEREDOC";
        default:             return "UNKNOWN";
    }
}

void print_tokens(t_token *tokens)
{
    int i = 0;
    printf("─── Lista de Tokens ───\n");
    while (tokens)
    {
        printf("\033[1;33m[%02d]\033[0m ", i);
        printf("type: \033[1;36m%-13s\033[0m  ", get_token_type_name(tokens->token_type));
        printf("value: \033[1;32m\"%s\"\033[0m\n", tokens->value);
        tokens = tokens->next;
        i++;
    }
    printf("────────────────────────\n\n");
}

void	print_commands(t_command *commands)
{
	int i = 0;
	t_command *cmd = commands;

	while (cmd)
	{
		printf("─── Comando %d ───\n", i + 1);

		// Argumentos (argv)
		if (cmd->argv)
		{
			printf("argv: ");
			for (int j = 0; cmd->argv[j]; j++)
				printf("[%s] ", cmd->argv[j]);
			printf("\n");
		}
		else
			printf("argv: (none)\n");

		// Redirecciones y flags
		printf("infile : %s\n", cmd->infile ? cmd->infile : "(none)");
		printf("outfile: %s\n", cmd->outfile ? cmd->outfile : "(none)");
		printf("heredoc: %s\n", cmd->heredoc ? cmd->heredoc : "(none)");
		printf("append : %s\n", cmd->append ? "yes" : "no");
		printf("pipe   : %s\n", cmd->pipe ? "yes" : "no");

		printf("\n");
		cmd = cmd->next;
		i++;
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
        minishell->tokens = tokenize_input(minishell->input);
		printf("quotes: %s\n", minishell->input);
		print_tokens(minishell->tokens);
		parser(&minishell->commands, minishell->tokens);
		print_commands(minishell->commands);
        free(minishell->input);
    }
    return (0);
}
