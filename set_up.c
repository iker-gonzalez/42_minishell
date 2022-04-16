/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/16 13:29:55 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_env(t_set *set, char **env)
{
	int		i;
	int		k;

	i = 0;
	while (env[i])
		i++ ;
	set->env = (char **)ft_calloc(sizeof(char *), i + 1);
	i = -1;
	k = 0;
	while (env[++i])
	{
		if ((ft_strncmp_len(env[i], "OLDPWD=", 7)) == 0 && ++i)
			set->env[k++] = ft_strdup(env[i]);
		else
			set->env[k++] = ft_strdup(env[i]);
	}
	set->env[i] = NULL;
}

void	ft_format_safe_paths(t_set *set)
{
	char	*path;
	char	**paths;
	int		i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		i++;
	set->safe_paths = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		set->safe_paths[i] = paths[i];
		i++;
	}
	set->safe_paths[i] = NULL;
	free(paths);
}

void	ft_format_paths(t_set *set)
{
	char	*path;
	char	**paths;
	int		i;

	path = ft_get_env_path(set, "PATH", 4);
	paths = ft_split(path, ':');
	if (!paths)
		return ;
	if (path)
		free(path);
	i = 0;
	while (paths[i])
		i++;
	set->paths = malloc(sizeof (char *) * (i + 1));
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		set->paths[i] = paths[i];
		i++;
	}
	set->paths[i] = NULL;
	free(paths);
}

void	set_up_shell(t_set *set, char **env)
{
	ft_get_env(set, env);
}
