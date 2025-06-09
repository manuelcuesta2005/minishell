#include "minishell.h"

// void	print_commands(t_command *commands)
// {
// 	int i = 0;
// 	t_command *cmd = commands;

// 	while (cmd)
// 	{
// 		printf("─── Comando %d ───\n", i + 1);

// 		Argumentos (argv)
// 		if (cmd->argv)
// 		{
// 			printf("argv: ");
// 			for (int j = 0; cmd->argv[j]; j++)
// 				printf("[%s] ", cmd->argv[j]);
// 			printf("\n");
// 		}
// 		else
// 			printf("argv: (none)\n");

// 		Redirecciones y flags
// 		printf("infile : %s\n", cmd->infile ? cmd->infile : "(none)");
// 		printf("outfile: %s\n", cmd->outfile ? cmd->outfile : "(none)");
// 		printf("heredoc: %s\n", cmd->heredoc ? cmd->heredoc : "(none)");
// 		printf("append : %s\n", cmd->append ? "yes" : "no");
// 		printf("pipe   : %s\n", cmd->pipe ? "yes" : "no");

// 		printf("\n");
// 		cmd = cmd->next;
// 		i++;
// 	}
// }


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_shell   *minishell;

    minishell = init_minishell();
    if (!minishell)
        return (1);
    get_variables(&minishell->env, envp);
    while (1)
    {
        minishell->input = readline("\033[1;34m⮞ \033[1;36m[minishell]\033[1;34m ⮜ \033[0;32mready$ \033[0m");
        if (!minishell->input)
            break;
        if (minishell->input[0] != '\0')
            add_history(minishell->input);
        pre_process(minishell);
        minishell->tokens = tokenize_input(minishell->input);
		parser(&minishell->commands, minishell->tokens);
		// print_commands(minishell->commands);
        free(minishell->input);
        free_tokens(minishell->tokens);
        free_command_list(minishell->commands);
    }
    free_env_list(minishell->env);
    free(minishell);
    return (0);
}
