/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parse_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:12:10 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/11 22:41:58 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    ft_check_double_out(t_proc *proc, int i, int *j)
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
    //else if (*j -1 >= 0 && ((proc->process[i][*j + 1]) == 126 || (proc->process[i][*j -1]) == 126))
      //  proc->added_spc++;
    else if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
    {
        if (proc->process[i][*j - 1] != 32 || proc->process[i][*j - 1] == 126)
            proc->added_spc++;
        if (proc->process[i][*j + 1] != 32 || proc->process[i][*j + 1] != 126)
            proc->added_spc++;
    }
}


void    ft_check_double_in(t_proc *proc, int i, int *j)
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
    //else if (*j -1 >= 0 && ((proc->process[i][*j + 1]) == 126 || (proc->process[i][*j -1]) == 126))
      //  proc->added_spc++;
    else
    {
        if (proc->red_in_arr[proc->red_in_arr_len++] == 1)
        {
            if (proc->process[i][*j - 1] != 32 || proc->process[i][*j - 1] != 126)
                proc->added_spc++;
            if (proc->process[i][*j + 1] != 32 || proc->process[i][*j + 1] != 126)
                proc->added_spc++;
        }
    }
}


void    ft_count_added_spaces(t_proc *proc, int i)
{
    int     j;

    ft_redirection_set_up(proc);
    j = 0;
    while (proc->process[i][j])
    {
        if (proc->process[i][j] == 62)
            ft_check_double_out(proc, i, &j);
        else if (proc->process[i][j] == 60)
            ft_check_double_in(proc, i, &j);
        j++;
    }
}