/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:21 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/22 10:57:43 by ikgonzal         ###   ########.fr       */
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
	proc->paths = malloc(sizeof (char *) * i);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = path;
		proc->paths[i] = paths[i]; 
		i++;
	}
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