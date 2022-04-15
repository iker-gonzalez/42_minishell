/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:38:51 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/14 18:41:29 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_red_condition_aux(t_proc *proc, int i, int *j, int *k)
{
	if (proc->red_out_del_arr_len < proc->red_out_del_count
		&& proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
	{
		ft_fill_double(proc, i, *j, k);
		(*j)++;
	}
	else
	{
		proc->aux[*k] = proc->process[i][*j];
		proc->aux[(*k) + 1] = proc->process[i][(*j) + 1];
		(*j)++;
		(*k)++;
	}
}
