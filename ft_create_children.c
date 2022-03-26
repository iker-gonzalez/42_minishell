/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:06:50 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/27 00:24:52 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_only_child(t_node *node, char **env)
{
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		execve(node->route, node->args, env);
		exit(0);
	}
}

void	ft_create_first_child(t_proc *proc, t_node *node, char **env)
{
	proc->launched_processes++;
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		close(proc->p[0][0]);
		dup2(proc->p[0][1], 1);
		close(proc->p[0][1]);
		dprintf(2, "INPUT 1: %d\n", proc->p[0][0]);
		dprintf(2, "INPUT 2: %d\n", proc->p[1][0]);
		dprintf(2, "OUTPUT 1: %d\n", proc->p[0][1]);
		dprintf(2, "OUTPUT 2: %d\n", proc->p[1][1]);
		execve(node->route, node->args, env);
		exit(0);
	}
	close(proc->p[0][0]);
//	ft_parental_wait((*proc->lst));
}

void	ft_create_last_child(t_proc *proc, t_node *node, char **env)
{
	proc->launched_processes++;
	if (proc->launched_processes % 2 == 0)
	{
		proc->pipe1 = 0;
		proc->pipe2 = 1;
	}
	else
	{
		proc->pipe1 = 1;
		proc->pipe2 = 0;
	}
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		dup2(proc->p[proc->pipe1][0], 0);
		close(proc->p[proc->pipe1][0]);
		close(proc->p[proc->pipe1][1]);
		dprintf(2, "INPUT 1: %d\n", proc->p[proc->pipe1][0]);
		dprintf(2, "INPUT 2: %d\n", proc->p[proc->pipe2][0]);
		dprintf(2, "OUTPUT 1: %d\n", proc->p[proc->pipe1][1]);
		dprintf(2, "OUTPUT 2: %d\n", proc->p[proc->pipe2][1]);
		execve(node->route, node->args, env);
		exit(0);
	}
	//ft_parental_wait((*proc->lst));
	close(proc->p[proc->pipe1][0]);
	close(proc->p[proc->pipe1][1]);
	close(proc->p[proc->pipe2][0]);
//	close(proc->p[proc->pipe2][1]);

}

void	ft_create_child(t_proc *proc, t_node *node, char **env)
{
	proc->launched_processes++;
	if (proc->launched_processes % 2 == 0)
	{
		proc->pipe1 = 0;
		proc->pipe2 = 1;
	}
	else
	{
		proc->pipe1 = 1;
		proc->pipe2 = 0;
	}
	pipe(proc->p[proc->pipe2]);
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		dup2(proc->p[proc->pipe1][0], 0);
		dup2(proc->p[proc->pipe2][1], 1);
		close(proc->p[proc->pipe2][1]);
		close(proc->p[proc->pipe1][0]);
		dprintf(2, "*********************************************\n");
		dprintf(2, "INPUT 1: %d\n", proc->p[proc->pipe1][0]);
		dprintf(2, "INPUT 2: %d\n", proc->p[proc->pipe2][0]);
		dprintf(2, "OUTPUT 1: %d\n", proc->p[proc->pipe1][1]);
		dprintf(2, "OUTPUT 2: %d\n", proc->p[proc->pipe2][1]);
		dprintf(2, "*********************************************\n");
		execve(node->route, node->args, env);
		exit(0);
	}
	//ft_parental_wait((*proc->lst));
	close(proc->p[proc->pipe1][1]);
	close(proc->p[proc->pipe1][0]);
	close(proc->p[proc->pipe2][1]);
	close(proc->p[proc->pipe2][0]);
}

void	ft_create_children(t_proc *proc)
{
	ft_set_route(proc);
	if ((*proc->lst)->previous == NULL && (*proc->lst)->next == NULL)
		ft_create_only_child((*proc->lst), proc->env);
	else if ((*proc->lst)->previous == NULL && (*proc->lst)->next != NULL)
		ft_create_first_child(proc, (*proc->lst), proc->env);
	else if ((*proc->lst)->previous != NULL && (*proc->lst)->next == NULL)
		ft_create_last_child(proc, (*proc->lst), proc->env);
	else
		ft_create_child(proc, (*proc->lst), proc->env);
}
