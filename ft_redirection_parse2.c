/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:05:15 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 21:50:25 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_double2(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j - 1] != 32
		&& proc->process[i][j + 2] != 32)
	{
		proc->aux[*k] = 32;
		if (proc->added_spc_arr_len < proc->added_spc)
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
		if (proc->added_spc_arr_len < proc->added_spc)
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
	}
	else
	{
		proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = proc->process[i][j];
	}
}

void	ft_fill_double(t_proc *proc, int i, int j, int *k)
{
	if (j == 0)
	{
		if (proc->process[i][j + 2] != 32)
			ft_no_space_after(proc, i, j, k);
		else
		{
			proc->aux[*k] = proc->process[i][j];
			*k += 1;
			proc->aux[*k] = proc->process[i][j];
		}
	}
	else if (proc->process[i][j - 1] != 32 && proc->process[i][j + 2] == 32)
		ft_no_space_before(proc, i, j, k);
	else if (proc->process[i][j + 2] != 32
			&& proc->process[i][j - 1] == 32)
	{
		ft_no_space_bfr_aftr(proc, i, j, k);
	}
	else
		ft_fill_double2(proc, i, j, k);
}

void	ft_fill_single2(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j - 1] != 32
		&& proc->process[i][j + 1] != 32)
	{
		proc->aux[*k] = 32;
		if (proc->added_spc_arr_len < proc->added_spc)
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
		if (proc->added_spc_arr_len < proc->added_spc)
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
	}
	else
		proc->aux[*k] = proc->process[i][j];
}

void	ft_fill_single(t_proc *proc, int i, int j, int *k)
{
	if (j == 0)
	{
		if (proc->process[i][j + 1] != 32)
			ft_no_space_after_single(proc, i, j, k);
		else
			proc->aux[*k] = proc->process[i][j];
	}
	else if (proc->process[i][j - 1] != 32 && proc->process[i][j + 1] == 32)
		ft_no_space_bfr_aftr_single(proc, i, j, k);
	else if (proc->process[i][j + 1] != 32
			&& (proc->process[i][j - 1] == 32))
	{
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
		if (proc->added_spc_arr_len < proc->added_spc)
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
	}
	else
		ft_fill_single2(proc, i, j, k);
}
