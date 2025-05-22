#include "../../include/minishell.h"

char    *remove_spaces(char *input)
{
    int i;
    int end;
    int len_input;
    char    *new_string = NULL;

    if (!input)
        return(NULL) ;
    i = 0;
    len_input = ft_strlen(input);
    end = len_input - 1;
    while (input[i] == ' ' || input[i] == '\t')
        i++;
    while (end >= i && (input[end] == ' ' || input[end] == '\t'))
        end--;
    if (i > end)
        return(ft_strdup(""));
    new_string = ft_substr(input, i, end - i + 1);
    return (new_string);
}

// int valid_parse(char *input)
// {

// }

// void    pre_process(char *input)
// {
//     char    *string;

//     if (!input)
//         return ;
//     string = remove_spaces(input);
// }