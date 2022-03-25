/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/25 18:29:37 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_piped(t_proc *proc)
{
	int	p[2];

	ft_set_route(proc);
	if ((*proc->lst)->previous == NULL && (*proc->lst)->next == NULL)
		ft_create_only_child((*proc->lst), proc->env);
	else if ((*proc->lst)->previous == NULL && (*proc->lst)->next != NULL)
	{
		if (pipe(p) == -1)
			printf("Error creating the pipe.");
		(*proc->lst)->fd[0] = 0;
		(*proc->lst)->fd[1] = p[1];
		ft_create_first_child((*proc->lst), proc->env);
	}
	else if ((*proc->lst)->previous != NULL && (*proc->lst)->next == NULL)
	{
		if (pipe(p) == -1)
			printf("Error creating the pipe.");
		(*proc->lst)->fd[0] = p[0];
		(*proc->lst)->fd[1] = 1;
		ft_create_last_child((*proc->lst), proc->env);
	}
	else
	{
		if (pipe(p) == -1)
			printf("Error creating the pipe.");
		(*proc->lst)->fd[0] = p[0];
		(*proc->lst)->fd[1] = p[1];
//		ft_create_child((*proc->lst), proc->env);
	}
}

void	ft_create_only_child(t_node *node, char **env)
{
	int	stt;

	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		execve(node->route, node->args, env);
		exit(0);
	}
	waitpid(node->pid, &stt, 0);
}

void	ft_create_first_child(t_node *node, char **env)
{
	int	stt;

	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		dup2(node->fd[1], 0);
		close(node->fd[0]);
		close(node->fd[1]);
		execve(node->route, node->args, env);
		exit(0);
	}
	waitpid(node->pid, &stt, 0);
}

void	ft_create_last_child(t_node *node, char **env)
{
	int	stt;

	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		dup2(node->fd[0], 1);
		dup2(node->fd[1], 1);
		close(node->fd[1]);
		close(node->fd[0]);
		execve(node->route, node->args, env);
		exit(0);
	}
	waitpid(node->pid, &stt, 0);
}

void	ft_set_route(t_proc *proc)
{
	int		i;
	char	**routes;

	i = 0;
	while (proc->paths[i])
		i++;
	routes = malloc (i * sizeof(char *)); 
	i = 0;
	while (proc->paths[i])
	{
		routes[i] = ft_strjoin(proc->paths[i], (*proc->lst)->args[0]);
		if (access(routes[i], F_OK) == 0)
			(*proc->lst)->route = routes[i];
		i++;
	}
}

/*void	ft_find_redi(t_proc *proc)
{
	
}*/

void	ft_print_fd(t_proc *proc)
{
	printf("INPUT: %d / OUTPUT: %d\n", (*proc->lst)->fd[0], (*proc->lst)->fd[1]);
	printf("ROUTE: %s\n", (*proc->lst)->route);
}

void	ft_process_fds(t_proc *proc)
{
	ft_lstiter(proc, ft_piped);
//	ft_lstiter(proc, ft_print_fd);
//	ft_lstiter(proc, ft_fd_red);
}




