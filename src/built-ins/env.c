
#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl_fd(env->value);
	return (0);

}
