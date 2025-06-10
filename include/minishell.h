#ifndef MINISHELL_H
#define MINISHELL_H
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "structs.h"
#include <unistd.h>
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

// Init program
t_command    *init_commands(void);
t_token      *init_tokens(void);
t_env        *init_env(void);
t_shell      *init_minishell(void);

// enviroment
char    *get_key(char *env);
char    *get_value(char *env);
void	new_env(t_env **env, char *key, char *value);
void    get_variables(t_env **env, char **envp);

// built-ins
int	ft_env(t_env *env);
int	ft_pwd(void);

// clean args
char    *remove_spaces(char *input);
void    normalize_spaces(char *input);
void    quotes_manage(char *input);
void    restore_quotes(char *input);
void    pre_process(t_shell *shell);

// tokenizer
int is_command(char *token);
int is_redirect(char *input);
int is_redirect_in(char *input);
int is_redirect_out(char *input);
t_token    *create_token(char *token, t_token_type token_type);
t_token	   *tokenize_input(char *input);

// Parser
t_command   *create_command(void);
void    update_command(t_command *command, t_token *token);
void    add_args_command(t_command *command, char *token);
int     command_empty(t_command *command);
void    add_command_list(t_command **commands, t_command *new);
int     can_execute(t_token *tokens);
void    parser(t_command **commands, t_token *tokens);

// redirect
int redirect_input(const char *filename);
int redirect_output(const char *filename);
int redirect_output_append(const char *filename);
int handle_heredoc(const char *delimiter);
int handle_redirection(const char *operator, const char *target);

// Free memory
void    free_env_list(t_env *env);
void    free_tokens(t_token *tokens);
void    free_command(t_command *commands);
void    free_command_list(t_command *commands);
void    free_minishell(t_shell *minishell);

#endif
