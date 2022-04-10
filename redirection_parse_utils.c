/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:12:10 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/10 08:29:24 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_check_double_out(t_proc *proc, int i, int *j)
{
    if (ft_strlen(proc->process[i]) - *j > 2)
    {
        if ((proc->process[i][*j + 1]) == 62)
        {
            *j += 1;
            if (proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
            {
                if (proc->process[i][*j - 1] != 32)
                    proc->added_spc++;
                if (proc->process[i][*j + 2] != 32)
                    proc->added_spc++;
            }
        }
        else
        {
            if (proc->red_out_arr[proc->red_out_arr_len] == 1)
            {
                proc->red_out_arr_len++;
                if (proc->process[i][*j - 1] != 32)
                    proc->added_spc++;
                if (proc->process[i][*j + 1] != 32)
                    proc->added_spc++;
            }
        }
    }
}

void    ft_check_double_in(t_proc *proc, int i, int *j)
{
    if (ft_strlen(proc->process[i]) - *j > 2)
    {
        if ((proc->process[i][*j + 1]) == 60)
        {
            *j += 1;
            if(proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
            {
                if (proc->process[i][*j - 1] != 32)
                    proc->added_spc++;
                if (proc->process[i][*j + 2] != 32)
                    proc->added_spc++;
            }
        }
        else
        {
            if (proc->red_in_arr[proc->red_in_arr_len] == 1)
            {
                proc->red_in_arr_len++;
                if (proc->process[i][*j - 1] != 32)
                    proc->added_spc++;
                if (proc->process[i][*j + 1] != 32)
                    proc->added_spc++;
            }
        }
    }
}


void    ft_count_added_spaces(t_proc *proc, int i)
{
    int     j;

   // while (proc->process[i])
    //{
        ft_redirection_set_up(proc);
        //if (ft_contain_red(proc->process[i]))
        //{   
            j = 0;
            while (proc->process[i][j])
            {
                if (proc->process[i][j] == 62)
                    ft_check_double_out(proc, i, &j);
                else if (proc->process[i][j] == 60)
                    ft_check_double_in(proc, i, &j);
                j++;
            }
        //}
        //i++;
   // }
}