/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:12:10 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 16:43:12 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_red_out(t_proc *proc, int i, int *j, int *red_out_arr_len)
{
	if (*red_out_arr_len < proc->red_out_count
		&& proc->red_out_arr[(*red_out_arr_len)++] == 1)
	{
		if (*j == 0)
		{
			if (proc->process[i][*j + 1] != 32
				|| proc->process[i][*j + 1] == 126)
				proc->added_spc++;
		}
		else
		{
			if (proc->process[i][*j - 1] != 32
				|| proc->process[i][*j - 1] == 126)
				proc->added_spc++;
			if (proc->process[i][*j + 1] != 32
				|| proc->process[i][*j + 1] != 126)
				proc->added_spc++;
		}
	}
}

void	ft_check_red_out_del(t_proc *proc, int i, int *j,
		int *red_out_del_arr_l)
{
	if (*red_out_del_arr_l < proc->red_out_del_count
		&& proc->red_out_del_arr[(*red_out_del_arr_l)++] == 1)
	{
		if (*j == 0)
		{
			if (proc->process[i][*j + 1] != 32
				|| proc->process[i][*j + 1] == 126)
				proc->added_spc++;
		}
		else
		{
			if (proc->process[i][*j - 1] != 32
				|| proc->process[i][*j - 1] == 126)
				proc->added_spc++;
			if (proc->process[i][*j + 2] != 32
				|| proc->process[i][*j - 1] == 126)
				proc->added_spc++;
		}
	}
	*j += 1;
}

void	ft_check_red_in(t_proc *proc, int i, int *j, int *red_in_arr_len)
{
	if (*red_in_arr_len < proc->red_in_count
		&& proc->red_in_arr[(*red_in_arr_len)++] == 1)
	{
		if (*j == 0)
		{
			if (proc->process[i][*j + 1] != 32
				|| proc->process[i][*j + 1] == 126)
				proc->added_spc++;
		}
		else
		{
			if (proc->process[i][*j - 1] != 32
				|| proc->process[i][*j - 1] != 126)
				proc->added_spc++;
			if (proc->process[i][*j + 1] != 32
				|| proc->process[i][*j + 1] != 126)
				proc->added_spc++;
		}
	}
}

void	ft_check_red_in_app(t_proc *proc, int i, int *j,
		int *red_in_app_arr_len)
{
	if (*red_in_app_arr_len < proc->red_in_app_count
		&& proc->red_in_app_arr[(*red_in_app_arr_len)++] == 1)
	{
		if (*j == 0)
		{
			if (proc->process[i][*j + 1] != 32
				|| proc->process[i][*j + 1] == 126)
				proc->added_spc++;
		}
		else
		{
			if (proc->process[i][*j - 1] != 32
				|| proc->process[i][*j - 1] == 126)
				proc->added_spc++;
			if (proc->process[i][*j + 2] != 32
				|| proc->process[i][*j + 2] == 126)
				proc->added_spc++;
		}
	}
	*j += 1;
}

void	ft_count_added_spaces(t_proc *proc, int i)
{
	int	j;
	int	red_out_arr_len;
	int	red_out_del_arr_len;
	int	red_in_arr_len;
	int	red_in_app_arr_len;

	proc->added_spc = 0;
	proc->added_spc_arr_len = 0;
	red_out_arr_len = proc->red_out_arr_len;
	red_out_del_arr_len = proc->red_out_del_arr_len;
	red_in_arr_len = proc->red_in_arr_len;
	red_in_app_arr_len = proc->red_in_app_arr_len;
	j = 0;
	while (proc->process[i][j])
	{
		if (proc->process[i][j] == 62 && proc->process[i][j + 1] == 62)
			ft_check_red_out_del(proc, i, &j, &red_out_del_arr_len);
		else if (proc->process[i][j] == 62)
			ft_check_red_out(proc, i, &j, &red_out_arr_len);
		else if (proc->process[i][j] == 60 && proc->process[i][j + 1] == 60)
			ft_check_red_in_app(proc, i, &j, &red_in_app_arr_len);
		else if (proc->process[i][j] == 60)
			ft_check_red_in(proc, i, &j, &red_in_arr_len);
		j++;
	}
}
