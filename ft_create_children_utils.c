/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_children_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:45:08 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/14 12:06:59 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_case_only_child(t_proc *proc)
{
	if ((*proc->lst)->is_built_in)
	{
		if ((*proc->lst)->has_red)
			ft_check_builtins(proc, (*proc->lst), 0, (*proc->lst)->args_red);
		else
			ft_check_builtins(proc, (*proc->lst), 0, (*proc->lst)->args);
	}
	else
		ft_create_child(NULL, NULL, (*proc->lst), proc);
}

void	ft_case_first_of_many(t_proc *proc)
{
	pipe(proc->rpipe);
	ft_create_child(NULL, proc->rpipe, (*proc->lst), proc);
	ft_swap_pipes(proc);
}

void	ft_case_middle_guy(t_proc *proc)
{
	pipe(proc->rpipe);
	ft_create_child(proc->lpipe, proc->rpipe, (*proc->lst), proc);
	ft_close_pipe(proc->lpipe);
	ft_swap_pipes(proc);
}

void	ft_case_last_of_many(t_proc *proc)
{
	ft_create_child(proc->lpipe, NULL, (*proc->lst), proc);
	ft_close_pipe(proc->lpipe);
}
