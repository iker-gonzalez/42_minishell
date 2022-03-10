/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:33 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/09 10:17:28 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quotations(t_proc *proc)
{
	int i;

	i = 0;
	proc->squote_count = 0;
	proc->dquote_count = 0;
	while(proc->line_read[i])
	{
		if(proc->line_read[i] == 34)
			proc->dquote_count++;
		else if (proc->line_read[i] == 39)
			proc->squote_count++;
		i++;
	}
}

void	ft_read_input(t_proc *proc)
{
	proc->line_read = readline(proc->prompt);
	add_history(proc->line_read);
	count_quotations(proc);
}

void	ft_lstiter(t_proc *proc, void (*f)(t_proc *))
{
	if (!f)
		return ;
	while ((*proc->lst))
	{
		f((proc));
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}
