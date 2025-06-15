#include "../../include/minishell.h"
#include "../../include/structs.h"

void	set_pwd(char *arg, char	*c)
{
	char	*string;

	string = ft_strjoin(arg, c);
	new_env(g_msh.env, string, NULL);
	free (string);
}

int	ft_cd(char *arg)
{
	char	c[9999];

	if (arg == NULL)
	{
		arg = get_env(g_msh.env, "HOME") + 5;
		if ((arg - 5) == NULL)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		if (arg[0] == '\0')
			return (1);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	set_pwd("OLDPWD=", c);
	getcwd(c, sizeof(c));
	set_pwd("PWD=", c);
	return (0);
}
