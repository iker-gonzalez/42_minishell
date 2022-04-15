/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:57:54 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/14 20:01:09 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_no_space_after_single(t_proc *proc, int i, int j, int *k)
{
	if (proc->process[i][j] != 126)
		proc->aux[*k] = proc->process[i][j];
	*k = *k + 1;
	proc->aux[*k] = 32;
	if (proc->added_spc_arr_len < proc->added_spc)
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
}

void	ft_no_space_bfr_aftr_single(t_proc *proc, int i, int j, int *k)
{
	proc->aux[*k] = 32;
	if (proc->added_spc_arr_len < proc->added_spc)
		proc->added_spc_arr[i][proc->added_spc_arr_len++] = *k;
	*k = *k + 1;
	if (proc->process[i][j] != 126)
		proc->aux[*k] = proc->process[i][j];
}
