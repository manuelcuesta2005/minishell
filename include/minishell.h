/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroson-m <nroson-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:39:21 by mcuesta-          #+#    #+#             */
/*   Updated: 2025/07/19 18:34:40 by nroson-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <unistd.h>

# define INPUT "\033[1;34m⮞ \033[1;36m[minishell]\033[1;34m ⮜ \033[0;32mready$ \033[0m"

// Init program
t_token		*init_tokens(void);
t_env		*init_env(void);
t_shell		*init_minishell(void);

// enviroment
char		*get_key(char *env);
char		*get_value(char *env);
char		*get_env(t_env *env, const char *key);
void		new_env(t_env **env, char *key, char *value);
void		get_variables(t_env **env, char **envp);

// built-ins
int			ft_echo(char **args);
int			ft_unset(char **a, t_shell *data);
int			ft_env(t_shell *data, char **args);
int			ft_pwd(void);
int			ft_cd(t_shell *env, char **args);
int			ft_export(t_shell *data, char **args);
void		ft_exit(char **arg, t_command *cmd, t_shell *shell);

// built-ins utils
bool		append_env_var(t_env **env, char *key, char *value);
bool		set_env_var(t_shell *data, char *key, char *value);
void		free_str_tab(char **tab);
char		**get_key_value_pair(char *argv);
bool		is_valid_env_var_key(char *var);
t_env		*get_env_var(t_env *env, char *key);
void		set_env(t_env **env, const char *key, const char *value);
char		*get_env_value(t_env *env, const char *key);
char		*get_cd_target(t_shell *env, char *arg);
char		*get_current_directory(char *cwd);
int			change_directory(const char *arg, char *oldpwd);
int			update_env_vars(t_shell *env, char *cwd, char *oldpwd);

// Lexer utils
char		*remove_spaces(char *input);
void		normalize_spaces(char *input);
void		quotes_manage(char *input);
void		restore_quotes(char *input);
int			should_expand(char *str);
void		pre_process(t_shell *shell);
t_token		*create_token(char *token, t_token_type token_type);

// tokenizer
int			is_command(char *token);
int			is_redirect(char *input);
t_token		*create_token(char *token, t_token_type token_type);
t_token		*lexer(t_shell *shell, char *input);

// Parser
t_command	*create_command(void);
void		update_command(t_command *command, t_token *token);
void		add_args_command(t_command *command, char *token);
int			command_empty(t_command *command);
void		add_command_list(t_command **commands, t_command *new);
int			can_execute(t_token *tokens);
void		parser(t_command **commands, t_token *tokens, t_shell *shell);
char		*remove_quotes(const char *arg);
char		*expand_variables(const char *input, t_env *env, int last_status);

// redirect
int			redirect_input(const char *filename);
int			redirect_output(const char *filename);
int			redirect_output_append(const char *filename);
int			handle_heredoc(const char *delimiter);
int			handle_redirection(const char *operator, const char *target);
int			create_heredoc(const char *delimiter, t_shell *shell);

// Free memory
void		free_env_list(t_env *env);
void		free_tokens(t_token *tokens);
void		free_command(t_command *commands);
void		free_command_list(t_command *commands);
void		free_minishell(t_shell *minishell);

// Executer
void		init_signals(void);
void		put_error(void);
int			apply_redirs(t_command *command);
int			exec_builtin(t_shell *shell, t_command *command);
char		*find_executable(char *command, t_env *envp);
int			executor_with_pipes(t_shell *shell);
int			only_execute(t_shell *shell, t_command *command, t_env *envp);
char		*filter_path(t_env *envp, char *key);
int			count_commands(t_command *commands);
void		close_and_free_pipes(int **pipes, int count);
void		close_all_pipes_in_child(int **pipes, int count);
int			executor(t_shell *shell);

// Utils
char		*ft_strjoin_free(char *s1, char *s2, int mode);
char		**env_list_to_array(t_env *envp);
void		ft_free_array(char **array);
int			only_execute(t_shell *shell, t_command *command, t_env *envp);

// error
char		*join_strs(char *str, char *add);
void		free_ptr(void *ptr);
int			errmsg_cmd(char *command, char *detail, char *error_message,
				int error_nb);
void		errmsg(char *errmsg, char *detail, int quotes);
bool		usage_message(bool return_val);

#endif
