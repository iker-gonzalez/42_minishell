/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:44:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/05 14:06:16 by ikgonzal         ###   ########.fr       */
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
			if ((*proc->lst)->content[i] == '<')
			{
				if ((*proc->lst)->content[i + 1] == '<')
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
			if ((*proc->lst)->content[i] == '>')
			{
				if ((*proc->lst)->content[i + 1] == '>')
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

int ft_quotes_together(t_node *node)
{

    int i;
    int ret;

    i = 0;
    ret = 0;
    while (node->content[i])
    {   
        if (node->content[i] == 34 && node->content[i + 1] == 39)
            ret = 1;
        else if (node->content[i] == 39 && node->content[i + 1] == 34)
            ret = 1;
        i++;
    }
    return (ret);
}

void    ft_parse_tquotes(t_proc *proc)
{
    int i;
    int lock;

    lock = 0;
    while (*proc->lst)
    {
        i = 0;
        if (ft_quotes_together((*proc->lst)))
        {
            (*proc->lst)->triple_quoted = 1;
            if (lock == 0 && (*proc->lst)->next)
                (*proc->lst) = (*proc->lst)->next;
            lock = 1;
            while((!ft_quotes_together((*proc->lst)) && (*proc->lst)->next))
            {
                (*proc->lst)->triple_quoted = 1;
                (*proc->lst) = (*proc->lst)->next;
            }
            lock = 0;
            if (ft_quotes_together((*proc->lst)))
                (*proc->lst)->triple_quoted = 1;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}
