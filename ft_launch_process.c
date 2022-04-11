/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/10 21:34:42 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>

char	*ft_get_abs_path(char *arg)
{
	int		bars;
	int		k;
	int		i;
	char	*path;
	
	bars = ft_findchar(arg, '/');
	i = 0;
	k = 0;
	while (arg[i] && k < bars)
	{
		if (arg[i] == '/')
			k++;
		i++;
	}
	path = malloc(sizeof(char) * i + 1);
	i = 0;
	k = 0;
	while (arg[i] && k < bars)
	{
		if (arg[i] == '/')
			k++;
		path[i] = arg[i];
		i++;
	}
	path[i] = '\0';
	return(path);
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
	while (proc->set->paths[i])
		i++;
	routes = malloc (i * sizeof(char *));
	i = 0;
	while (proc->set->paths[i])
	{
		routes[i] = ft_strjoin(proc->set->paths[i], arg);
		if (access(routes[i], F_OK) == 0)
		{
			(*proc->lst)->route = ft_strdup(routes[i]);
			free (routes[i]);
		}
		else
			free(routes[i]);
		i++;
	}
	free (routes);
}

void	ft_parental_wait(t_proc *proc)
{
	int		stt;
	pid_t	process;

	stt = 0;
	process = waitpid((*proc->lst)->pid, &stt, 0);
	if (WIFEXITED(stt))
	{
		g_sig.act_child = 0;
		g_sig.exit_status = WEXITSTATUS(stt);
	}
}

void	ft_is_built_in(t_node *node, int index)
{
	if ((ft_strncmp_len(node->args[index], "env", 3)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "pwd", 3)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "cd", 2)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "export", 6)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "unset", 5)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "exit", 4)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp(node->args[index], "echo", 4)) == 0
			&& ft_strlen(node->args[index]) == 4)
		node->is_built_in = 1;
	else
		node->is_built_in = 0;
}

void	ft_set_process_type(t_proc *proc)
{
	if ((*proc->lst)->args[0][0] != 60 || (*proc->lst)->args[0][0] != 62)
		ft_is_built_in((*proc->lst), 0);
	else
		ft_is_built_in((*proc->lst), 3);
}

void	ft_launch_process(t_proc *proc)
{
	ft_lstiter(proc, ft_set_process_type);
	ft_lstiter(proc, ft_create_children);
	ft_lstiter(proc, ft_parental_wait);
}
