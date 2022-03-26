/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/26 07:58:02 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_env(t_proc *proc, char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++ ;
	proc->env = (char **)ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (env[++i])
	{
		if ((ft_strncmp(env[i], "OLDPWD", 6)) != 0)
			proc->env[i] = ft_strdup(env[i]);
	}
	proc->env[i] = NULL;
}

void	ft_format_paths(t_proc *proc)
{
	char	*path;
	char	**paths;
	int	i;

	path = getenv("PATH");
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
		i++;
	proc->paths = malloc(sizeof (char *) * (i + 1));
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		proc->paths[i] = paths[i]; 
		i++;
	}
	proc->paths[i] = NULL;
	free(paths);
}

void	set_up_shell(t_proc *proc, char **env)
{
	char *user;
	char *logo;

	user = getenv("USER");
	logo = "\033[38;2;243;134;48mpapa$hell 🐚\033[0m";
	proc->prompt = ft_strjoin(user, logo);
	ft_format_paths(proc);
	ft_get_env(proc, env);
}
