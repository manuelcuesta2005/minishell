#include "../../include/minishell.h"
#include "../../include/structs.h"

static char	**get_key_value_pair(char *argv)
{
	char	**tmp;
	char	*same_pos;

	same_pos = ft_strchr(argv, '=');
	tmp = malloc(sizeof * tmp * (2 + 1));
	tmp[0] = ft_substr(argv, 0, same_pos - argv);
	tmp[1] = ft_substr(same_pos, 1, ft_strlen(same_pos));
	tmp[2] = NULL;
	return (tmp);
}

int	export_builtin(t_shell *data, char **args)
{
}
