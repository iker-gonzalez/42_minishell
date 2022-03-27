/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:06:50 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/27 20:27:25 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_child(int *lpipe, int *rpipe, t_node *node, char **env)
{
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
	{
		if (lpipe)
			ft_set_read(lpipe);
		if (rpipe)
			ft_set_write(rpipe);
		execve(node->route, node->args, env);
		exit(0);
	}
}

void	ft_create_children(t_proc *proc)
{
	ft_set_route(proc);
	if ((*proc->lst)->previous == NULL && (*proc->lst)->next == NULL)
		ft_create_child(NULL, NULL, (*proc->lst), proc->env);
	else if ((*proc->lst)->previous == NULL && (*proc->lst)->next != NULL)
	{
		pipe(proc->rpipe);
		ft_create_child(NULL, proc->rpipe, (*proc->lst), proc->env);
		ft_swap_pipes(proc);
	}
	else if ((*proc->lst)->previous != NULL && (*proc->lst)->next == NULL)
	{
		ft_create_child(proc->lpipe, NULL, (*proc->lst), proc->env);
		ft_close_pipe(proc->lpipe);
	}
	else
	{
		pipe(proc->rpipe);
		ft_create_child(proc->lpipe, proc->rpipe, (*proc->lst), proc->env);
		ft_close_pipe(proc->lpipe);
		ft_swap_pipes(proc);
	}
}
