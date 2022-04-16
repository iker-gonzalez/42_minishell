/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:11:23 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/16 13:24:01 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_abs_path(char *arg)
{
	int		bars;
	int		k;
	int		i;
	char	*path;

	bars = ft_findchar(arg, '/');
	i = 0;
	k = 0;
	while (arg[i++] && k < bars)
		k += ft_char_match(arg[i], '/');
	path = malloc(sizeof(char) * i + 1);
	i = 0;
	k = 0;
	while (arg[i] && k < bars)
	{
		k += ft_char_match(arg[i], '/');
		path[i] = arg[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

int	ft_check_if_path(t_proc *proc)
{
	int	k;

	k = -1;
	while (proc->set->env[++k])
	{
		if ((ft_strncmp_len(proc->set->env[k], "PATH=", 5)) == 0)
			return (1);
	}
	return (0);
}

void	ft_check_if_route(t_proc *proc, char *arg)
{
	int		i;
	char	*path;

	path = ft_get_abs_path(arg);
	i = -1;
	while (proc->set->safe_paths[++i])
	{
		if ((ft_strncmp(proc->set->safe_paths[i], arg,
					ft_strlen(proc->set->safe_paths[i])) == 0))
			(*proc->lst)->route = arg;
	}
}

void	ft_is_route(char *route, t_proc *proc, char *path, char *arg)
{
	route = ft_strjoin(path, arg);
	if (access(route, F_OK) == 0)
	{
		(*proc->lst)->route = ft_strdup(route);
		free (route);
	}
	else
		free(route);
}

void	ft_set_route(t_proc *proc, char *arg)
{
	int		i;
	char	**routes;

	if (!arg)
		return ;
	if (arg[0] == '/' && !ft_check_if_path(proc))
		ft_check_if_route(proc, (*proc->lst)->args[0]);
	ft_format_paths(proc->set);
	i = 0;
	if (!proc->set->paths)
		return ;
	while (proc->set->paths[i])
		i++;
	routes = malloc (i * sizeof(char *));
	i = 0;
	while (proc->set->paths[i])
	{
		ft_is_route(routes[i], proc, proc->set->paths[i], arg);
		i++;
	}
	free (routes);
}
