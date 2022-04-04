/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/04 20:47:51 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_env(t_set *set, char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++ ;
	set->env = (char **)ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (env[++i])
	{
		if ((ft_strncmp(env[i], "OLDPWD", 6)) != 0)
			set->env[i] = ft_strdup(env[i]);
	}
	set->env[i] = NULL;
}

void	ft_format_paths(t_set *set)
{
	char	*path;
	char	**paths;
	int		i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
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
	ft_format_paths(set);
}
