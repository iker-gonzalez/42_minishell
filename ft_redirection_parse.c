/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:20:51 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/09 10:09:16 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_double_out(t_proc *proc, int i, int *j)
{
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
			if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
			{
				if (proc->process[i][*j - 1] != 32)
					proc->added_spc++;
				if (proc->process[i][*j + 1] != 32)
					proc->added_spc++;
			}
		}
	}
}

void	ft_check_double_in(t_proc *proc, int i, int *j)
{
	if (ft_strlen(proc->process[i]) - *j > 2)
	{
		if ((proc->process[i][*j + 1]) == 60
			&& proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
		{
			if (proc->process[i][*j - 1] != 32)
				proc->added_spc++;
			if (proc->process[i][*j + 2] != 32)
				proc->added_spc++;
			*j += 1;
		}
		else
		{
			if (proc->red_in_arr[proc->red_in_arr_len++] == 1)
			{
				if (proc->process[i][*j - 1] != 32)
					proc->added_spc++;
				if (proc->process[i][*j + 1] != 32)
					proc->added_spc++;
			}
		}
	}
}

void	ft_fill_single(t_proc *proc, int i, int j, int *k)
{
	if (ft_strlen(proc->process[i]) - j > 1)
	{
		if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
		{
			if (proc->process[i][j - 1] != 32 && proc->process[i][j + 1] == 32)
			{
				proc->aux[*k] = 32;
				*k += 1;
				proc->aux[*k] = proc->process[i][j];
			}
			else if (proc->process[i][j + 1] != 32
					&& proc->process[i][j - 1] == 32)
			{
				proc->aux[*k] = proc->process[i][j];
				*k += 1;
				proc->aux[*k] = 32;
			}
			else if (proc->process[i][j - 1] != 32
					&& proc->process[i][j + 1] != 32)
			{
				proc->aux[*k] = 32;
				*k += 1;
				proc->aux[*k] = proc->process[i][j];
				*k += 1;
				proc->aux[*k] = 32;
			}
			else
				proc->aux[*k] = proc->process[i][j];
		}
	}
}

void	ft_fill_double(t_proc *proc, int i, int j, int *k)
{
	if (ft_strlen(proc->process[i]) - j > 2)
	{
		if (proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
		{
			if (proc->process[i][j - 1] != 32 && proc->process[i][j + 2] == 32)
			{
				proc->aux[*k] = 32;
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
			}
			else if (proc->process[i][j - 1] != 32
					&& proc->process[i][j + 2] != 32)
			{
				proc->aux[*k] = 32;
				*k += 1;
				proc->aux[*k] = proc->process[i][j];
				*k += 1;
				proc->aux[*k] = proc->process[i][j];
				*k += 1;
				proc->aux[*k] = 32;
			}
			else
			{
				proc->aux[*k] = proc->process[i][j];
				*k += 1;
				proc->aux[*k] = proc->process[i][j];
			}
		}
	}
}

void	ft_redirection_parse(t_proc *proc)
{
	int		i;
	int		j;
	int		k;

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
			ft_redirection_set_up(proc);
			proc->aux = malloc(sizeof(char) * (ft_strlen(proc->process[i])
					+ proc->added_spc + 1));
			ft_memset(proc->aux, 0, ft_strlen(proc->process[i])
				+ proc->added_spc + 1);
			j = 0;
			k = 0;
			while (proc->process[i][j] && ft_strlen(proc->process[i]) > j)
			{
				if (proc->process[i][j] == 62 && proc->process[i][j + 1] != 62)
					ft_fill_single(proc, i, j, &k);
				else if (proc->process[i][j] == 62
						&& proc->process[i][j + 1] == 62)
				{
					ft_fill_double(proc, i, j, &k);
					j++;
				}
				else if (proc->process[i][j] == 60
						&& proc->process[i][j + 1] == 60)
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
			printf("AUX: %s\n", proc->aux);
		}
		i++;
	}
}
