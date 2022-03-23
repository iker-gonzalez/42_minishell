/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/23 19:31:59 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	set_up_shell(t_proc *proc)
{
	char *user;
	char *logo;

	user = getenv("USER");
	logo = "\033[38;2;243;134;48mpapa$hell 🐚\033[0m";
	proc->prompt = ft_strjoin(user, logo);
	ft_format_paths(proc);

}
