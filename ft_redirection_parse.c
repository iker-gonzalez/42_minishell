/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:20:51 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/11 12:55:27 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_fill_single(t_proc *proc, int i, int j, int *k)
{
    if (ft_strlen(proc->process[i]) - j > 1)
    {
        if (proc->process[i][j - 1] != 32 && proc->process[i][j + 1] == 32)
        {
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
        }
        else if (proc->process[i][j + 1] != 32
                && proc->process[i][j - 1] == 32)
        {
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
        }
        else if (proc->process[i][j - 1] != 32
                && proc->process[i][j + 1] != 32)
        {
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
        }
        else
            proc->aux[*k] = proc->process[i][j];
    }
}

void    ft_fill_double(t_proc *proc, int i, int j, int *k)
{
    if (ft_strlen(proc->process[i]) - j > 2)
    {
        if (proc->process[i][j - 1] != 32 && proc->process[i][j + 2] == 32)
        {
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
        }
        else if (proc->process[i][j + 2] != 32
                && proc->process[i][j - 1] == 32)
        {
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
        }
        else if (proc->process[i][j - 1] != 32
                && proc->process[i][j + 2] != 32)
        {
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = 32;
			proc->added_spc_arr[i][proc->added_spc_arr_len++] = 1;
        }
        else
        {
            proc->aux[*k] = proc->process[i][j];
            *k += 1;
            proc->aux[*k] = proc->process[i][j];
        }
    }
}

void    ft_redirection_parse(t_proc *proc)
{
    int     i;
    int     j;
    int     k;

    i = 0;
	proc->added_spc_arr = (int **) malloc (proc->process_count * sizeof(int *));
    while (i < proc->process_count)
    {
        j = 0;
        k = 0;
        ft_count_added_spaces(proc , i);
		proc->added_spc_arr[i] = (int *) malloc (proc->added_spc * sizeof(int));
		ft_memset(proc->added_spc_arr[i], 0, sizeof(int *));
        proc->aux = malloc(sizeof(char) * (ft_strlen(proc->process[i]) + proc->added_spc + 1));
        ft_redirection_set_up(proc);
        ft_memset(proc->aux, 0, ft_strlen(proc->process[i]) + proc->added_spc + 1);
        while (proc->process[i][j] && ft_strlen(proc->process[i]) > j)
        {
            if (proc->process[i][j] == 62 && proc->process[i][j + 1] != 62
                && proc->red_out_arr[proc->red_out_arr_len++] == 1)
                    ft_fill_single(proc, i, j, &k);
            else if (proc->process[i][j] == 60 && proc->process[i][j + 1] != 60
                    && proc->red_in_arr[proc->red_in_arr_len++] == 1)
                ft_fill_single(proc, i, j, &k);
            else if (proc->process[i][j] == 62 && proc->process[i][j + 1] == 62)
            {
                if(proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
                {
                    ft_fill_double(proc, i, j, &k);
                    j++;
                }
                else
                {
                    proc->aux[k] = proc->process[i][j];
                    proc->aux[k + 1] = proc->process[i][j + 1];
                    j++;
                    k++;
                }
            }
            else if (proc->process[i][j] == 60 && proc->process[i][j + 1] == 60)
            {
                if(proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
                {
                    ft_fill_double(proc, i, j, &k);
                    j++;
                }
                else
                {
                    proc->aux[k] = proc->process[i][j];
                    proc->aux[k + 1] = proc->process[i][j + 1];
                    j++;
                    k++;
                }
            }
            else
                proc->aux[k] = proc->process[i][j];
            j++;
            k++;
        }
        proc->aux[k] = '\0';
        free(proc->process[i]);
        proc->process[i] = malloc(ft_strlen(proc->aux) + 1);
        proc->process[i] = ft_strdup(proc->aux);
        i++;
    }
}
