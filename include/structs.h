#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum e_token_type
{
    T_COMMAND,
    T_FLAG,
    T_ARGV,
    T_PIPE,
    T_REDIRECT_IN,
    T_REDIRECT_OUT,
    T_APPEND,
    T_HEREDOC,
} t_token_type;

typedef struct s_token
{
    t_token_type token_type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_command
{
    char **argv;
    char *infile;
    char *outfile;
    int append;
    int heredoc;
    struct s_command *next;
} t_command;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell
{
    int history;
    int exit;
    char *input;
    t_env *env;
    t_token *tokens;
    t_command *commands;
} t_shell;


#endif