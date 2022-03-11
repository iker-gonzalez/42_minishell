/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:39 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/11 22:33:33 by ikgonzal         ###   ########.fr       */
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
        proc->pipe_arr = malloc(sizeof(int) * pipe_count + 1);
}

void    ft_parse_red_in(t_proc *proc)
{
    int i;
    int red_in;
    int red_in_app;

    i = 0;
    red_in = 0;
    red_in_app = 0;
    proc->red_in_arr_len = 0;
    proc->red_in_app_arr_len = 0;
    while (proc->line_read[i])
    {
        if (proc->line_read[i] == 60 && proc->line_read[i + 1] == 60)
        {
            red_in_app++;
            i++;
        }
        else if (proc->line_read[i] == 60 && proc->line_read[i + 1] != 60)
            red_in++;
        i++;
    }
    if (red_in)
        proc->red_in_arr = malloc(sizeof(int) * red_in + 1);
    else if (red_in_app)
        proc->red_in_app_arr = malloc (sizeof(int) * red_in_app + 1);
    printf("red_in_count: %d\n", red_in);
    printf("red_in_app_count: %d\n", red_in_app);
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
        proc->red_in_arr = malloc(sizeof(int) * red_out + 1);
    else if (red_out_del)
        proc->red_in_app_arr = malloc (sizeof(int) * red_out_del + 1);
    printf("red_out_count: %d\n", red_out);
    printf("red_out_del_count: %d\n", red_out_del);
}

void    ft_parse_input(t_proc *proc)
{
    ft_parse_pipes(proc);
    ft_parse_red_in(proc);
    ft_parse_red_out(proc);
}
