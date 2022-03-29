/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:57:14 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 11:22:37 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

char	*ft_get_env_path(t_proc *proc, char *var, int var_len)
{
	int		i;
	char	*path;
	int		path_len;
	int		k;
	int		j;

	i = -1;
	while (proc->env[++i])
	{
		if (ft_strncmp(proc->env[i], var, var_len) == 0)
		{
			path_len = ft_strlen(proc->env[i]) - var_len;
			path = malloc(sizeof(char) * path_len +1);
			j = 0;
			k = 0;
			while (proc->env[i][j++])
			{
				if (j > var_len)
					path[k++] = proc->env[i][j];
			}
			path[k] = '\0';
			return (path);
		}
	}
	return (NULL);
}

int	ft_go_to_home(t_proc *proc)
{
	char	*home_path;

	home_path = ft_get_env_path(proc, "HOME", 4);
	if (!home_path)
	{
		ft_putendl_fd("papa$hell: cd: HOME not set", 2);
		return (1);
	}
	else
	{
		ft_update_oldpwd(proc);
		chdir(home_path);
	}
	free(home_path);
	return (0);
}

int	ft_go_to_oldpwd(t_proc *proc)
{
	char	*old_pwd_path;

	old_pwd_path = ft_get_env_path(proc, "OLDPWD", 6);
	if (!old_pwd_path)
	{
		ft_putendl_fd("papa$shell: cd: OLDPWD not set", 2);
		return (1);
	}
	else
	{
		ft_update_oldpwd(proc);
		chdir(old_pwd_path);
	}
	free(old_pwd_path);
	return (0);
}

int	ft_update_oldpwd(t_proc *proc)
{
	char		oldpwd_path[PATH_MAX];
	char		*var;
	static int	old_pwd;

	if (getcwd(oldpwd_path, PATH_MAX) == NULL)
		return (1);
	var = ft_strjoin("OLDPWD=", oldpwd_path);
	if (!old_pwd)
	{
		proc->env = add_var(proc, var);
		old_pwd = 1;
	}
	else
		edit_var(proc, var);
	free (var);
	return (0);
}

int	ft_cd(char **argv, t_proc *proc)
{
	if (argv[1] && (ft_strncmp(argv[1], "-", 1)) == 0)
		ft_go_to_oldpwd(proc);
	else if (!argv[1])
		ft_go_to_home(proc);
	else
	{
		ft_update_oldpwd(proc);
		chdir(argv[1]);
	}
	return (0);
}
