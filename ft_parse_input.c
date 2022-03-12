/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:39 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/12 12:24:05 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_parse_pipes(t_proc *proc)
{
    int i;
    int pipe_count;
    int pipe_exp_len;
    
    i = 0;
    pipe_count = 0;
    pipe_exp_len = 0;
    while (proc->line_read[i])
    {
        if (proc->line_read[i] == 124)
            pipe_count++;
        i++;
    }
    if (pipe_count)
        proc->pipe_arr = malloc(sizeof(int) * pipe_count);
}

void    ft_parse_red_in(t_proc *proc)
{
    int i;

    i = 0;
    proc->red_in_arr_len = 0;
    proc->red_in_app_arr_len = 0;
	proc->red_in_count = 0;
	proc->red_in_app_count = 0;
    while (proc->line_read[i])
    {
        if (proc->line_read[i] == 60 && proc->line_read[i + 1] == 60)
        {
            proc->red_in_app_count++;
            i++;
        }
        else if (proc->line_read[i] == 60 && proc->line_read[i + 1] != 60)
            proc->red_in_count++;
        i++;
    }
    if (proc->red_in_count)
        proc->red_in_arr = malloc(sizeof(int) * proc->red_in_count + sizeof(int));
    else if (proc->red_in_app_count)
    	proc->red_in_app_arr = malloc (sizeof(int) * proc->red_in_app_count + sizeof(int));
}

void    ft_parse_red_out(t_proc *proc)
{
    int i;
    int red_out;
    int red_out_del;

    i = 0;
    red_out = 0;
    red_out_del = 0;
    proc->red_out_arr_len = 0;
    proc->red_out_del_arr_len = 0;
    while (proc->line_read[i])
    {
        if (proc->line_read[i] == 62 && proc->line_read[i + 1] == 62)
        {
            red_out_del++;
            i++;
        }
        else if (proc->line_read[i] == 62 && proc->line_read[i + 1] != 62)
            red_out++;
        i++;
    }
    if (red_out)
        proc->red_in_arr = malloc(sizeof(int) * red_out);
    else if (red_out_del)
        proc->red_in_app_arr = malloc (sizeof(int) * red_out_del);
    printf("red_out_count: %d\n", red_out);
    printf("red_out_del_count: %d\n", red_out_del);
}

void    ft_parse_input(t_proc *proc)
{
    ft_parse_pipes(proc);
    ft_parse_red_in(proc);
    ft_parse_red_out(proc);
}
