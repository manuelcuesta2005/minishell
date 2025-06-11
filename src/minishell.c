#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_shell   *minishell;

    minishell = init_minishell();
    if (!minishell)
        return (1);
    get_variables(&minishell->env, envp);
	init_signals();
    while (1)
    {
        minishell->input = readline("\033[1;34m⮞ \033[1;36m[minishell]\033[1;34m ⮜ \033[0;32mready$ \033[0m");
        if (!minishell->input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
            break;
		}
        if (minishell->input[0] != '\0')
            add_history(minishell->input);
        pre_process(minishell);
        minishell->tokens = tokenize_input(minishell->input);
        minishell->commands = NULL;
		parser(&minishell->commands, minishell->tokens);
        free(minishell->input);
        free_tokens(minishell->tokens);
        free_command_list(minishell->commands);
    }
    free_env_list(minishell->env);
    free(minishell);
    return (0);
}
