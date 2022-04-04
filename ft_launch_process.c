/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/04 20:24:47 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <stdio.h>

void	ft_set_route(t_proc *proc)
{
	int		i;
	char	**routes;

	ft_format_paths(proc->set);
	i = 0;
	while (proc->set->paths[i])
		i++;
	routes = malloc (i * sizeof(char *));
	i = 0;
	while (proc->set->paths[i])
	{
		routes[i] = ft_strjoin(proc->set->paths[i], (*proc->lst)->args[0]);
		if (access(routes[i], F_OK) == 0)
			(*proc->lst)->route = routes[i];
		else
			free(routes[i]);
		i++;
	}
}

void	ft_parental_wait(t_proc *proc)
{
	int		stt;
	pid_t	process;

	process = waitpid((*proc->lst)->pid, &stt, 0);
	if (WIFEXITED(stt))
		proc->set->exit_status = WEXITSTATUS(stt);
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
	else if ((ft_strncmp(node->args[index], "echo", 4)) == 0)
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
