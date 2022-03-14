/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/14 19:51:02 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_tokens(t_proc *proc, char *process)
{
	int i;

	i = 0;
	proc->token_count = 1;
	while (process[i])
	{
		if (process[i] == 32 && proc->space_arr[proc->space_arr_len++] == 2)
		{
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
		proc->space_arr_len += 2;
		i++;
	}
}