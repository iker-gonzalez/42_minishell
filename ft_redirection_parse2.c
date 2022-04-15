/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:05:15 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 11:01:36 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_on_spc_arr(t_proc *proc, int i, int k)
{
	if (proc->added_spc_arr_len < proc->added_spc)
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = k;
}

void	ft_fill_double2(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j + 2] != 32
			&& proc->process[i][j - 1] == 32)
	{
		ft_copy_on_aux(proc, i, j, (*k)++);
		ft_copy_on_aux(proc, i, j, (*k)++);
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, *k);
	}
	else if (proc->process[i][j - 1] != 32
		&& proc->process[i][j + 2] != 32)
	{
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, (*k)++);
		ft_copy_on_aux(proc, i, j, (*k)++);
		ft_copy_on_aux(proc, i, j, (*k)++);
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, *k);
	}
	else
	{
		ft_copy_on_aux(proc, i, j, (*k)++);
		ft_copy_on_aux(proc, i, j, *k);
	}
}

void	ft_fill_double(t_proc *proc, int i, int j, int *k)
{
	if (j == 0)
	{
		if (proc->process[i][j + 2] != 32)
		{
			ft_copy_on_aux(proc, i, j, (*k)++);
			ft_copy_on_aux(proc, i, j, (*k)++);
			proc->aux[*k] = 32;
			ft_copy_on_spc_arr(proc, i,*k);
		}
		else
		{
			ft_copy_on_aux(proc, i, j, (*k)++);
			ft_copy_on_aux(proc, i, j, *k);
		}
	}
	else if (proc->process[i][j - 1] != 32 && proc->process[i][j + 2] == 32)
	{
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, (*k)++);
		ft_copy_on_aux(proc, i, j, (*k)++);
		ft_copy_on_aux(proc, i, j, *k);
	}
	else
		ft_fill_double2(proc, i, j, k);
}

void	ft_fill_single2(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j + 1] != 32
			&& (proc->process[i][j - 1] == 32))
	{
		ft_copy_on_aux(proc, i, j, (*k)++);
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, *k);
	}
	else if (proc->process[i][j - 1] != 32
		&& proc->process[i][j + 1] != 32)
	{
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, (*k)++);
		ft_copy_on_aux(proc, i, j, (*k)++);
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, *k);
	}
	else
		ft_copy_on_aux(proc, i, j, (*k)++);
}

void	ft_fill_single(t_proc *proc, int i, int j, int *k)
{
	if (j == 0)
	{
		if (proc->process[i][j + 1] != 32)
		{
			ft_copy_on_aux(proc, i, j, (*k)++);
			proc->aux[*k] = 32;
			ft_copy_on_spc_arr(proc, i, *k);
		}
		else
			ft_copy_on_aux(proc, i, j, (*k)++);
	}
	else if (proc->process[i][j - 1] != 32 && proc->process[i][j + 1] == 32)
	{
		proc->aux[*k] = 32;
		ft_copy_on_spc_arr(proc, i, (*k)++);
		ft_copy_on_aux(proc, i, j, *k);
	}
	else
		ft_fill_single2(proc, i, j, k);
}
