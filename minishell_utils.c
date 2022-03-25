/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:34:04 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/25 13:00:26 by jsolinis         ###   ########.fr       */
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
    return (0);
}

void	ft_exp_sp_arr(t_proc *proc)
{
	int i;
	int k;

	i = -1;
	proc->exp_sp_arr_len = 0;
	while (++i < proc->space_count)
	{
		if (proc->space_arr[i] != 1)
			proc->exp_sp_arr_len++;
	}
	proc->exp_sp_arr = malloc(sizeof(int) * proc->exp_sp_arr_len);
	i = -1;
	k = 0;
	while (++i < proc->space_count)
	{
		if (proc->space_arr[i] != 1)
			proc->exp_sp_arr[k++] = proc->space_arr[i];
	}
	proc->exp_space_count = k;
}
