#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    // t_shell *minishell;
    (void)argc;
    (void)argv;
    t_shell   *minishell;

    minishell = (t_shell *) malloc(sizeof(t_shell));
    if (!minishell)
        return (1);
    get_variables(&minishell->env, envp);
    printf("%s\n", minishell->env);
    // while (1)
    // {
    //     // minishell->input = readline("\033[1;34m⮞ \033[1;36m[minishell]\033[1;34m ⮜ \033[0;32mready$ \033[0m");
    //     // add_history(minishell->input);
    //     free(minishell->input);
    // }
    return (0);
}