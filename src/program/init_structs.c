#include "minishell.h"

t_command    *init_commands(void)
{
    t_command   *commands;

    commands = (t_command *) malloc(sizeof(t_command));
    if (!commands)
        return (NULL);
    commands->argv = NULL;
    commands->append = NULL;
    commands->heredoc = NULL;
    commands->infile = NULL;
    commands->outfile = NULL;
    commands->pipe = 0;
    commands->next = NULL;
    return (commands);
}

t_token    *init_tokens(void)
{
    t_token *tokens;

    tokens = (t_token *) malloc(sizeof(t_token));
    if (!tokens)
        return (NULL);
    tokens->token_type = T_ARGV;
    tokens->value = NULL;
    tokens->next = NULL;
    return (tokens);
}

t_env    *init_env(void)
{
    t_env   *env;

    env = (t_env *) malloc(sizeof(t_env));
    if (!env)
        return (NULL);
    env->key = NULL;
    env->value = NULL;
    env->next = NULL;
    return (env);
}

t_shell *init_minishell(void)
{
    t_shell *minishell;

    minishell = (t_shell *) malloc(sizeof(t_shell));
    if (!minishell)
        return (NULL);
    minishell->input = NULL;
    minishell->history = 0;
    minishell->tokens = NULL;
    minishell->commands = init_commands();
    minishell->env = init_env();
    if (!minishell->commands || !minishell->env)
    {
        free_command_list(minishell->commands);
        free_env_list(minishell->env);
        free(minishell);
        return (NULL);
    }
    return (minishell);
}
