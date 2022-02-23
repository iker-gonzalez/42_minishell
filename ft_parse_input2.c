/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:44:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/02/23 13:35:41 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_parse_pipe(t_proc *proc)
{
	int	i;

	while (*proc->lst)
	{
		i = 0;
		while ((*proc->lst)->content[i])
		{
			if ((*proc->lst)->content[i] == '|')
				(*proc->lst)->pipe = 1;
			i++;
		}
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}

void    ft_parse_red_in(t_proc *proc)
{
	int	i;

	while (*proc->lst)
	{
		i = 0;
		while ((*proc->lst)->content[i])
		{
			if ((*proc->lst)->content[i] == '>')
			{
				if ((*proc->lst)->content[i + 1] == '>')
				{
					(*proc->lst)->red_in_append = 1;
					i++;
				}
				else
					(*proc->lst)->red_in = 1;
			}
			i++;
		}
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}

void    ft_parse_red_out(t_proc *proc)
{
	int	i;

	while (*proc->lst)
	{
		i = 0;
		while ((*proc->lst)->content[i])
		{
			if ((*proc->lst)->content[i] == '<')
			{
				if ((*proc->lst)->content[i + 1] == '<')
				{
					(*proc->lst)->red_out_del = 1;
					i++;
				}
				else
					(*proc->lst)->red_out = 1;
			}
			i++;
		}
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}