/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:20:51 by jsolinis          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/09 12:28:59 by ikgonzal         ###   ########.fr       */
=======
/*   Updated: 2022/04/09 16:25:05 by jsolinis         ###   ########.fr       */
>>>>>>> 665ae66a054333ce09a8670ddb36405dec0bcb87
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_check_double_out(t_proc *proc, int i, int *j)
{
<<<<<<< HEAD
	if (ft_strlen(proc->process[i]) - *j > 2)
	{
		if ((proc->process[i][*j + 1]) == 62
			&& proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
		{
			if (proc->process[i][*j - 1] != 32)
				proc->added_spc++;
			if (proc->process[i][*j + 2] != 32)
				proc->added_spc++;
			*j += 1;
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
=======
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
>>>>>>> 665ae66a054333ce09a8670ddb36405dec0bcb87
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

<<<<<<< HEAD
	i = 0;
	while (i < proc->process_count)
	{
		ft_redirection_set_up(proc);
		if (ft_contain_red(proc->process[i]))
		{	
			j = 0;
			while (proc->process[i][j])
			{
				if (proc->process[i][j] == 62)
					ft_check_double_out(proc, i, &j);
				else if (proc->process[i][j] == 60)
					ft_check_double_in(proc, i, &j);
				j++;
			}
			proc->aux = malloc(sizeof(char) * (ft_strlen(proc->process[i])
					+ proc->added_spc + 1));
			ft_redirection_set_up(proc);
			ft_memset(proc->aux, 0, ft_strlen(proc->process[i])
				+ proc->added_spc + 1);
			ft_red_spc(proc);
			j = 0;
			k = 0;
			while (proc->process[i][j] && ft_strlen(proc->process[i]) > j)
			{
				if (proc->process[i][j] == 62 && proc->process[i][j + 1] != 62
					&& proc->red_out_arr[proc->red_out_arr_len++] == 1)
					ft_fill_single(proc, i, j, &k);
				else if (proc->process[i][j] == 60 && proc->process[i][j + 1] != 60
						&& proc->red_in_arr[proc->red_in_arr_len++] == 1)
					ft_fill_single(proc, i, j, &k);
				else if (proc->process[i][j] == 62 && proc->process[i][j + 1] == 62
					&& proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
				{
					ft_fill_double(proc, i, j, &k);
					j++;
				}
				else if (proc->process[i][j] == 60 && proc->process[i][j + 1] == 60
						&& proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
				{
					ft_fill_double(proc, i, j, &k);
					j++;
				}
				else
					proc->aux[k] = proc->process[i][j];
				j++;
				k++;
			}
			proc->aux[k] = '\0';
			free(proc->process[i]);
			proc->process[i] = malloc(ft_strlen(proc->aux) + 1);
			proc->process[i] = proc->aux;
			printf("PROC->PROC: %s\n", proc->process[i]);
		}
		i++;
	}
=======
    i = 0;
    while (i < proc->process_count)
    {
        ft_redirection_set_up(proc);
        if (ft_contain_red(proc->process[i]))
        {   
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
        i++;
    }
    i = 0;
	proc->added_spc_arr = (int **) malloc (proc->process_count * sizeof(int *));
    while (i < proc->process_count)
    {
        j = 0;
        k = 0;
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
        proc->process[i] = proc->aux;
        printf("PROC->PROC: %s\n", proc->process[i]);
        i++;
    }
>>>>>>> 665ae66a054333ce09a8670ddb36405dec0bcb87
}
