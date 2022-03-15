/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/15 14:32:36 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_redirections(t_proc *proc, char *process, int *i)
{
	if (process[*i] == 60)
	{
		if (process[*i+1] == 60)
		{
			if(proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
			{
				proc->token_count++;
			}
			*i += 2;
		}
		else if (proc->red_in_arr[proc->red_in_arr_len++] == 1)
		{
			proc->token_count++;
			if (process[*i+1] == 32)
				proc->token_count++;
			*i += 1;
		}
	}
	else if (process[*i] == 62)
	{
		if (process[*i+1] == 62)
		{
			if(proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
			{
				proc->token_count++;
			}
			*i += 2;
		}
		else if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
		{
			proc->token_count++;
			if (process[*i+1] == 32)
				proc->token_count++;
			*i += 1;
		}
	}
}

void	ft_count_tokens(t_proc *proc, char *process)
{
	int i;
	int k;
	
	i = 0;
	if (ft_strlen(proc->line_read) > 0)
		proc->token_count = 1;
	proc->red_in_arr_len = 0;
	proc->red_in_app_arr_len = 0;
	proc->red_out_arr_len = 0;
	proc->red_out_del_arr_len = 0;
	while (process[i])
	{
		k = proc->token_count;
		if (process[i] == 32 && proc->space_arr[proc->space_arr_len++] != 3 && process[i+1] != 32)
		{
			proc->token_count++;
		}
		else if ((process[i] == 60 || process[i] == 62) && (process[i-1] != 32 || process[i+1] != 32))
		{
			ft_check_redirections(proc, process, &i);
			if (k != proc->token_count/* && process[i+1] != 32 && process[i-1] != 32*/)
					proc->token_count++;
		}
		i++;
	}
	printf("Token count: %d\n", proc->token_count);
}


void	ft_arrange_input(t_proc *proc)
{
	int i;

	i = 0;
	proc->space_arr_len = 0;
	while (i < proc->process_count)
	{
		ft_count_tokens(proc, proc->process[i]);
		ft_gen_lst(proc);
		if (i < proc->process_count)
			proc->space_arr_len += 2;
		i++;
	}
}

