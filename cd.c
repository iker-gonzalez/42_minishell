/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:57:14 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 16:17:26 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

char	*ft_get_env_path(t_set *set, char *var, int v_l)
{
	int		i;
	char	*path;
	int		k;
	int		j;

	i = -1;
	while (set->env[++i])
	{
		if (ft_strncmp(set->env[i], var, v_l) == 0
			&& set->env[i][v_l] == '=')
		{
			path = malloc(sizeof(char) * (ft_strlen(set->env[i])) - v_l + 1);
			j = 0;
			k = 0;
			while (set->env[i][j++])
			{
				if (j > v_l)
					path[k++] = set->env[i][j];
			}
			path[k] = '\0';
			return (path);
		}
	}
	return (NULL);
}

int	ft_go_to_home(t_set *set)
{
	char	*home_path;
	int		cd_ret;

	home_path = ft_get_env_path(set, "HOME", 4);
	if (!home_path)
	{
		free(home_path);
		ft_putendl_fd("papa$hell: cd: HOME not set", 2);
		return (1);
	}
	else
	{
		ft_update_oldpwd(set);
		cd_ret = chdir(home_path);
	}
	free(home_path);
	return (cd_ret);
}

int	ft_go_to_oldpwd(t_set *set)
{
	char	*old_pwd_path;
	int		cd_ret;

	old_pwd_path = ft_get_env_path(set, "OLDPWD", 6);
	if (!old_pwd_path)
	{
		free(old_pwd_path);
		ft_putendl_fd("papa$shell: cd: OLDPWD not set", 2);
		return (1);
	}
	else
	{
		ft_update_oldpwd(set);
		cd_ret = chdir(old_pwd_path);
	}
	free(old_pwd_path);
	return (cd_ret);
}

int	ft_update_oldpwd(t_set *set)
{
	char		oldpwd_path[PATH_MAX];
	char		*var;
	static int	old_pwd;

	if (getcwd(oldpwd_path, PATH_MAX) == NULL)
		return (1);
	var = ft_strjoin("OLDPWD=", oldpwd_path);
	if (!old_pwd)
	{
		set->env = add_var(set, var);
		old_pwd = 1;
	}
	else
		edit_var(set, var);
	free(var);
	return (0);
}

int	ft_cd(char **argv, t_set *set, int child)
{
	int	cd_ret;

	if (argv[1] && (ft_strncmp(argv[1], "-", 1)) == 0)
		cd_ret = ft_go_to_oldpwd(set);
	else if (!argv[1])
		cd_ret = ft_go_to_home(set);
	else
	{
		ft_update_oldpwd(set);
		cd_ret = chdir(argv[1]);
	}
	if (cd_ret == -1 && child)
		print_error(": No such file or directory", 1, argv[1], 1);
	else if (cd_ret == -1 && !child)
		print_error(": No such file or directory", 1, argv[1], 0);
	else if (cd_ret == 0 && child)
		exit (0);
	return (0);
}
