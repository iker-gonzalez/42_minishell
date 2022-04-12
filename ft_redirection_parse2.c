/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:05:15 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/12 13:29:17 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_double2(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j - 1] != 32
		&& proc->process[i][j + 2] != 32)
	{
		proc->aux[*k] = 32;
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
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
	if (proc->process[i][j - 1] != 32 && proc->process[i][j + 2] == 32)
	{
		proc->aux[*k] = 32;
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
	}
	else if (proc->process[i][j + 2] != 32
			&& proc->process[i][j - 1] == 32)
	{
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
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
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
	}
	else
		proc->aux[*k] = proc->process[i][j];
}

void	ft_fill_single(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j - 1] != 32 && proc->process[i][j + 1] == 32)
	{
		proc->aux[*k] = 32;
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
		*k += 1;
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
	}
	else if (proc->process[i][j + 1] != 32
			&& (proc->process[i][j - 1] == 32))
	{
		if (proc->process[i][j] != 126)
			proc->aux[*k] = proc->process[i][j];
		*k += 1;
		proc->aux[*k] = 32;
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
	}
	else
		ft_fill_single2(proc, i, j, k);
}
