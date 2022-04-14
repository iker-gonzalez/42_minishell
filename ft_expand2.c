/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 10:20:11 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 15:14:00 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_red_in(t_proc *proc, char c, int *i)
{		
	if (proc->lock && c == 60)
	{
		if (proc->line_read[*i] == 60 && proc->line_read[*i + 1] == 60)
		{
			if ((!proc->single_quote) && (!proc->double_quote))
				proc->red_in_app_arr[proc->red_in_app_arr_len++] = 1;
			else
				proc->red_in_app_arr[proc->red_in_app_arr_len++] = 2;
			proc->line_expanded[proc->line_exp_len] = proc->line_read[*i];
			proc->line_exp_len++;
			*i += 1;
		}
		else
		{
			if ((!proc->single_quote) && (!proc->double_quote))
				proc->red_in_arr[proc->red_in_arr_len] = 1;
			else
				proc->red_in_arr[proc->red_in_arr_len] = 2;
			proc->red_in_arr_len++;
		}
	}
}

void	ft_expand_red_out(t_proc *proc, char c, int *i)
{		
	if (proc->lock && c == 62)
	{
		if (proc->line_read[*i] == 62 && proc->line_read[*i + 1] == 62)
		{
			if ((!proc->single_quote) && (!proc->double_quote))
				proc->red_out_del_arr[proc->red_out_del_arr_len++] = 1;
			else
				proc->red_out_del_arr[proc->red_out_del_arr_len++] = 2;
			proc->line_expanded[proc->line_exp_len] = proc->line_read[*i];
			proc->line_exp_len++;
			*i += 1;
		}
		else
		{
			if ((!proc->single_quote) && (!proc->double_quote))
				proc->red_out_arr[proc->red_out_arr_len] = 1;
			else
				proc->red_out_arr[proc->red_out_arr_len] = 2;
			proc->red_out_arr_len++;
		}
	}
}

void	ft_expand_spaces(t_proc *proc, char c, int *i)
{
	if (proc->lock && c == 32)
	{
		if (*i - 1 >= 0 && (!proc->single_quote) && (!proc->double_quote)
			&& proc->line_read[*i - 1] != 32 && proc->line_read[*i - 1] != 124
			&& proc->line_read[*i + 1] != 124 && proc->line_read[*i + 1])
			proc->space_arr[proc->space_arr_len++] = 2;
		else if (proc->line_read[*i + 1] == 32
			&& (!proc->single_quote) && (!proc->double_quote))
			proc->space_arr[proc->space_arr_len++] = 1;
		else if ((!proc->single_quote) && (!proc->double_quote))
			proc->space_arr[proc->space_arr_len++] = 1;
		else
			proc->space_arr[proc->space_arr_len++] = 3;
	}
}

void	ft_expand_exit(t_proc *proc)
{
	char	*g_exit_status_arr;
	int		j;

	g_exit_status_arr = ft_itoa(g_exit_status);
	j = 0;
	while (proc->lock && g_exit_status_arr && g_exit_status_arr[j])
		proc->line_expanded[proc->line_exp_len++] = g_exit_status_arr[j++];
	if (g_exit_status_arr && !proc->lock)
		proc->line_exp_len += ft_strlen(g_exit_status_arr)
			+ ft_strlen(proc->line_read) - 2;
	free (g_exit_status_arr);
}

void	ft_expand_pipe(t_proc *proc, char c)
{
	if (proc->lock && c == 124)
	{
		if ((!proc->single_quote) && (!proc->double_quote))
			proc->pipe_arr[proc->pipe_arr_len++] = 1;
		else
			proc->pipe_arr[proc->pipe_arr_len++] = 2;
	}
}
