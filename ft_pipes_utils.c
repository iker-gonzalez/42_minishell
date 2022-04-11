/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:22:55 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/11 19:26:15 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_set_read(int *lpipe)
{
	dup2(lpipe[0], STDIN_FILENO);
	ft_close_pipe(lpipe);
}

void	ft_set_write(int *rpipe)
{
	dup2(rpipe[1], STDOUT_FILENO);
	ft_close_pipe(rpipe);
}

void	ft_swap_pipes(t_proc *proc)
{
	proc->lpipe[0] = proc->rpipe[0];
	proc->lpipe[1] = proc->rpipe[1];
}
