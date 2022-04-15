/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:54:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/15 16:42:12 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_on_aux(t_proc *proc, int i, int j, int k)
{
	if (proc->process[i][j] != 126)
		proc->aux[k] = proc->process[i][j];
}

void	ft_redirection_set_up(t_proc *proc)
{
	proc->red_out_arr_len = 0;
	proc->red_in_arr_len = 0;
	proc->red_out_del_arr_len = 0;
	proc->red_in_app_arr_len = 0;
}

void	ft_check_red_out_type(t_proc *proc, int i, int *j)
{
	if ((*proc->lst)->args[i][*j + 1] == 62
		&& proc->red_out_del_arr_len < proc->red_out_del_count
		&& proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
	{
		ft_set_red_out_app(proc, i);
		(*proc->lst)->has_red = 1;
		(*j)++;
	}
	else
	{
		if (proc->red_out_arr_len < proc->red_out_count
			&& proc->red_out_arr[proc->red_out_arr_len++] == 1)
		{
			ft_set_red_out(proc, i);
			(*proc->lst)->has_red = 1;
		}
	}
}

void	ft_check_red_in_type(t_proc *proc, int i, int *j)
{
	if ((*proc->lst)->args[i][*j + 1] == 60
		&& proc->red_in_app_arr_len < proc->red_in_app_count
		&& proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
	{
		ft_set_red_in_del(proc, i);
		(*proc->lst)->has_red = 1;
		(*j)++;
	}
	else
	{
		if (proc->red_in_arr_len < proc->red_in_count
			&& proc->red_in_arr[proc->red_in_arr_len++] == 1)
		{
			ft_set_red_in(proc, i);
			(*proc->lst)->has_red = 1;
		}
	}
}

void	ft_check_if_red(t_proc *proc)
{
	int	i;
	int	j;

	i = 0;
	(*proc->lst)->has_red = 0;
	while ((*proc->lst)->args[i])
	{
		j = 0;
		while ((*proc->lst)->args[i][j])
		{
			if ((*proc->lst)->args[i][j] == 62)
				ft_check_red_out_type(proc, i, &j);
			else if ((*proc->lst)->args[i][j] == 60)
				ft_check_red_in_type(proc, i, &j);
			j++;
		}
		i++;
	}
}
