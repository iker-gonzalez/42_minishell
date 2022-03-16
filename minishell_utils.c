/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:34:04 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/16 16:45:04 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_findchar(char *line, char c)
{
    int i;
    int k;

    i = 0;
    k = 0;
    if (line[i])
    {
        while(line[i])
        {
            if ((line[i]) == c)
                k++;
            i++;
        }
    }
    return (k);
}

int     ft_find_red(t_proc *proc, char *process, int *i)
{
    if (process[*i] == 60 && process[*i+1] == 60)
    {
        if (proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
        {
            *i +=1;
            return(1);
        }
    }
}