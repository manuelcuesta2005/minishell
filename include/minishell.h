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

// enviroment
char    *get_key(char *env);
char    *get_value(char *env);
void	new_env(t_env **env, char *key, char *value);
void    get_variables(t_env **env, char **envp);

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

// redirect
int redirect_input(const char *filename);
int redirect_output(const char *filename);
int redirect_output_append(const char *filename);
int handle_heredoc(const char *delimiter);
int handle_redirection(const char *operator, const char *target);

// built-ins
int	ft_env(t_env *env);
int	ft_pwd(void);
#endif
