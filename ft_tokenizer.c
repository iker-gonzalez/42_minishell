/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:40:25 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/12 20:18:22 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_process_count(t_proc *proc)
{
    int i;

    i = 0;
    proc->process_count = 0;
    while (i < proc->pipe_arr_len)
    {
        if (proc->pipe_arr[i] == 1)
            proc->process_count++;
        i++;
    }
    proc->process_count++;
    printf("process count: %d\n", proc->process_count);
}

void    ft_mem_tokenizer(t_proc *proc)
{
    int row;
    int col;
    int j;
    int i;
    
    proc->pipe_arr_len = 0;
    proc->space_arr_len = 0;
    proc->tokens = (char **)malloc(sizeof(char *) * (proc->process_count + 1));
    row = 0;
    i = 0;
    while (row < proc->process_count)
    {
        col = 0;
        j = 0;
        while (proc->line_expanded[i])
        {
            if (proc->line_expanded[i] == 124 && proc->pipe_arr[proc->pipe_arr_len++] == 1 && ++i)
                break ;
            //else if (proc->line_expanded[i] == 32 && proc->space_arr[proc->space_arr_len++] == 1)
            //    j++;
            col++;
            i++;
        }
        printf("proc %d: space allocated %d\n", row, (col - j + 1));
        proc->tokens[row] = malloc(sizeof(char) * (col - j + 1));
        row++;
    }
}

void    ft_tokenizer(t_proc *proc)
{
    int row;
    int col;
    int i;
    
    proc->pipe_arr_len = 0;
    proc->space_arr_len = 0;
    row = 0;
    i = 0;
    while (row < proc->process_count)
    {
        col = 0;
        while (proc->line_expanded[i])
        {
            if (proc->line_expanded[i] == 124 && proc->pipe_arr[proc->pipe_arr_len++] == 1 && ++i)
                break ;
            //else if (proc->line_expanded[i] == 32 && proc->space_arr[proc->space_arr_len++] == 1)
                //i++;
            else
                proc->tokens[row][col++] = proc->line_expanded[i++];
        }
        proc->tokens[row][col] = '\0';
        row++;
    }
}


