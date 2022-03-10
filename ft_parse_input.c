/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:39 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/10 14:24:41 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_findchar(t_node *node, char c)
{
    int i;
    int k;

    i = 0;
    k = 0;
    if (node)
    {
        while(node->content[i])
        {
            if ((node->content[i]) == c)
                k++;
            i++;
        }
    }
    return (k);
}

void    ft_parse_dollar(t_proc *proc)
{
    int i;

    while (*proc->lst)
    {
        i = 0;
        while ((*proc->lst)->content[i])
        {
            if ((*proc->lst)->content[i] == '$')
            {
                if ((*proc->lst)->content[i + 1] == '?')
                    (*proc->lst)->dollar_exit = 1;
                else
                    (*proc->lst)->dollar = 1;
            }
            i++;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}

void    ft_parse_dquotes(t_proc *proc, char c)
{
    int lock;

    lock = 0;
    while (*proc->lst)
    {
        if (ft_findchar(*proc->lst, c))
        {
            (*proc->lst)->double_quoted = 1;
            if (lock == 0 && (*proc->lst)->next && (ft_findchar((*proc->lst), c) %2) != 0)
                (*proc->lst) = (*proc->lst)->next;
            lock = 1;
            while (!ft_findchar((*proc->lst), c) && (*proc->lst)->next)
            {
                (*proc->lst)->double_quoted = 1;
                (*proc->lst) = (*proc->lst)->next;
            }
            lock = 0;
            if (ft_findchar((*proc->lst), c))
                (*proc->lst)->double_quoted = 1;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}

void    ft_parse_squotes(t_proc *proc, char c)
{
    int lock;

    lock = 0;
    while (*proc->lst)
    {
        if (ft_findchar(*proc->lst, c))
        {
            (*proc->lst)->single_quoted = 1;
            if (lock == 0 && (*proc->lst)->next && (ft_findchar((*proc->lst), c) %2) != 0)
                (*proc->lst) = (*proc->lst)->next;
            lock = 1;
            while (!ft_findchar((*proc->lst), c) && (*proc->lst)->next)
            {
                (*proc->lst)->single_quoted = 1;
                (*proc->lst) = (*proc->lst)->next;
            }
            lock = 0;
            if (ft_findchar((*proc->lst), c))
                (*proc->lst)->single_quoted = 1;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}

void    ft_count_pipes(t_proc *proc)
{
    int i;
    
    i = 0;
    proc->pipe_count = 0;
    while (proc->line_read[i])
    {
        if (proc->line_read[i] == 124)
            proc->pipe_count++;
        i++;
    }
    printf("pipe_count: %d\n", proc->pipe_count);
    proc->pipe_exp = malloc(sizeof(int) * proc->pipe_count);
    ft_bzero(proc->pipe_exp, proc->pipe_count);
}

void    ft_parse_input(t_proc *proc)
{
    ft_gen_lst(proc);
    ft_parse_squotes(proc, 39);
    ft_parse_dquotes(proc, 34);
	ft_parse_tquotes(proc);
    ft_parse_dollar(proc);
    ft_parse_pipe(proc);
    ft_parse_red_in(proc);
    ft_parse_red_out(proc);
    ft_count_pipes(proc);
}
