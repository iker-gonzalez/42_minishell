/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/25 12:43:58 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_piped(t_proc *proc)
{
	int	p[2];

	if ((*proc->lst)->previous == NULL && (*proc->lst)->next == NULL)
	{
		(*proc->lst)->fd[0] = 0;
		(*proc->lst)->fd[1] = 1;
	}
	else if ((*proc->lst)->previous == NULL && (*proc->lst)->next != NULL)
	{
		if (pipe(p) == -1)
			printf("Error creating the pipe.");
		(*proc->lst)->fd[0] = 0;
		(*proc->lst)->fd[1] = p[1];
	}
	else if ((*proc->lst)->previous != NULL && (*proc->lst)->next == NULL)
	{
		if (pipe(p) == -1)
			printf("Error creating the pipe.");
		(*proc->lst)->fd[0] = p[0];
		(*proc->lst)->fd[1] = 1;
	}
	else
	{
		if (pipe(p) == -1)
			printf("Error creating the pipe.");
		(*proc->lst)->fd[0] = p[0];
		(*proc->lst)->fd[1] = p[1];
	}
}

void	ft_create_child(t_proc *proc)
{
	proc->lst->pid = fork();
	if (proc->lst->pid < 0)
		perror("fork failed");
	if (proc->lst->pid == 0)
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(
	}
}

/*void	ft_find_redi(t_proc *proc)
{
	
}*/

void	ft_print_fd(t_proc *proc)
{
	printf("INPUT: %d / OUTPUT: %d\n", (*proc->lst)->fd[0], (*proc->lst)->fd[1]);
}

void	ft_process_fds(t_proc *proc)
{
	ft_lstiter(proc, ft_cmd_exist);
	ft_lstiter(proc, ft_piped);
	ft_lstiter(proc, ft_print_fd);
//	ft_lstiter(proc, ft_fd_red);
}




