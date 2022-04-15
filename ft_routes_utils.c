/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:11:23 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/14 14:04:29 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_match(char c, char match)
{
	int	ret;

	ret = 0;
	if (c == match)
		ret++;
	return (ret);
}

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

char	*ft_set_abs_path(t_proc *proc, char *arg)
{
	char	*cmd;
	char	*var;
	char	*path;

	cmd = NULL;
	path = ft_get_abs_path(arg);
	if (arg[0] == '/')
	{
		cmd = ft_strrchr(arg, '/');
		var = ft_strjoin("PATH=", path);
		free(path);
		edit_var(proc->set, var);
		free(var);
	}
	return (cmd);
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
	if (arg[0] == '/' || arg[0] == '.')
		arg = ft_set_abs_path(proc, arg);
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
