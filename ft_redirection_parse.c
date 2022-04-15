/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_parse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:18:30 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 18:16:26 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection_parse_set_up(t_proc *proc, int i)
{
	int	quote_count;

	ft_count_added_spaces(proc, i);
	proc->added_spc_arr[i] = (int *) malloc (proc->added_spc * sizeof(int));
	proc->added_spc_arr_length[i] = (int *) malloc(sizeof (int));
	proc->added_spc_arr_length[i][0] = proc->added_spc;
	quote_count = ft_findchar(proc->process[i], 126);
	proc->aux = malloc(sizeof(char) * (ft_strlen(proc->process[i])
				+ proc->added_spc - quote_count + 1));
}

void	ft_check_red_condition2(t_proc *proc, int i, int *j, int *k)
{
	if (proc->process[i][*j] == 60 && proc->process[i][(*j) + 1] == 60)
	{
		if (proc->red_in_app_arr_len < proc->red_in_app_count
			&& proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
		{
			ft_fill_double(proc, i, *j, k);
			(*j)++;
		}
		else
		{
			proc->aux[*k] = proc->process[i][*j];
			proc->aux[(*k) + 1] = proc->process[i][(*j) + 1];
			(*j)++;
			(*k)++;
		}
	}
	else if (proc->process[i][*j] != 126)
		proc->aux[*k] = proc->process[i][*j];
}

void	ft_check_red_condition(t_proc *proc, int i, int *j, int *k)
{	
	if (proc->process[i][*j] == 62 && proc->process[i][(*j) + 1] != 62
		&& proc->red_out_arr_len < proc->red_out_count
		&& proc->red_out_arr[proc->red_out_arr_len++] == 1)
		ft_fill_single(proc, i, *j, k);
	else if (proc->process[i][*j] == 60 && proc->process[i][(*j) + 1] != 60
		&& proc->red_in_arr_len < proc->red_in_count &&
		proc->red_in_arr[proc->red_in_arr_len++] == 1)
		ft_fill_single(proc, i, *j, k);
	else if (proc->process[i][*j] == 62 && proc->process[i][(*j) + 1] == 62)
		ft_check_red_condition_aux(proc, i, j, k);
	else
		ft_check_red_condition2(proc, i, j, k);
}

void	ft_aux_copy(t_proc *proc, int i)
{
	free(proc->process[i]);
	proc->process[i] = NULL;
	proc->process[i] = ft_strdup(proc->aux);
}

void	ft_redirection_parse(t_proc *proc)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	proc->added_spc_arr = (int **) malloc (proc->process_count * sizeof(int *));
	proc->added_spc_arr_length = (int **) malloc (proc->process_count
			* sizeof(int *));
	ft_redirection_set_up(proc);
	while (++i < proc->process_count)
	{
		j = -1;
		k = 0;
		ft_redirection_parse_set_up(proc, i);
		while (proc->process[i][++j] && ft_strlen(proc->process[i]) > j)
		{
			ft_check_red_condition(proc, i, &j, &k);
			if (proc->process[i][j] != 126)
				k++;
		}
		proc->aux[k] = '\0';
		ft_aux_copy(proc, i);
		if (proc->aux)
			free (proc->aux);
	}
}
