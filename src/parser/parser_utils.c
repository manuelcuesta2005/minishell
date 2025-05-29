#include "minishell.h"

t_command   *create_command(void)
{
    t_command   *new_command;

    new_command = (t_command *) malloc(sizeof(t_command));
    if (!new_command)
        return (NULL);
    new_command->argv = NULL;
    new_command->infile = NULL;
    new_command->outfile = NULL;
    new_command->heredoc = NULL;
    new_command->append = NULL;
    new_command->pipe = 0;
    new_command->next = NULL;
    return(new_command);
}

void    update_command(t_command *command, t_token *token)
{
    char    *value;

    value = ft_strdup(token->next->value);
    if (token->token_type == T_REDIRECT_IN)
        command->infile = value;
    else if (token->token_type == T_REDIRECT_OUT)
        command->outfile = value;
    else if (token->token_type == T_APPEND)
        command->append = value;
    else if (token->token_type == T_HEREDOC)
        command->heredoc = value;
    else if (token->token_type == T_PIPE)
        command->pipe = 1;
}

void    add_args_command(t_command *command, char *token)
{
    int i;
    int j;
    char    **args;

    i = 0;
    j = 0;
    while (command->argv && command->argv[i])
        i++;
    args = malloc(sizeof(char *) * (i + 2));
    if (!args)
        return ;
    while (j < i)
    {
        args[j] = ft_strdup(command->argv[j]);
        j++;
    }
    args[i] = ft_strdup(token);
    args[i + 1] = NULL;
    free(command->argv);
    command->argv = args;
}

void    add_command_list(t_command **commands, t_command *new)
{
    t_command   *temporal;

    if (!*commands)
    {
        *commands = new;
        return ;
    }
    temporal = *commands;
    while (temporal->next)
        temporal = temporal->next;
    temporal->next = new;
}
