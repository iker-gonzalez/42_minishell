/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proceniser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:40:25 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 16:39:26 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process_count(t_proc *proc)
{
	int	i;

	i = 0;
	proc->process_count = 0;
	while (i < proc->pipe_arr_len)
	{
		if (proc->pipe_arr[i] == 1)
			proc->process_count++;
		i++;
	}
	proc->process_count++;
}

void	ft_mem_proceniser(t_proc *proc)
{
	int	row;
	int	col;
	int	j;
	int	i;

	proc->process = (char **)malloc(sizeof(char *) * (proc->process_count + 1));
	row = 0;
	i = 0;
	while (row < proc->process_count)
	{
		col = 0;
		j = 0;
		while (proc->line_expanded[i++] && ++col)
		{
			if (proc->line_expanded[i] == 124
				&& proc->pipe_arr[proc->pipe_arr_len] == 1 && ++i)
				break ;
			else if (proc->line_expanded[i] == 32
				&& proc->space_arr[proc->space_arr_len++] == 1)
				j++;
		}
		proc->process[row] = malloc(sizeof(char) * (col + 1));
		row++;
	}
}

void	ft_fill_proceniser(t_proc *proc)
{
	int	row;
	int	col;
	int	i;

	row = 0;
	i = 0;
	while (row < proc->process_count)
	{
		col = 0;
		while (proc->line_expanded[i])
		{
			if (proc->line_expanded[i] == 124
				&& proc->pipe_arr[proc->pipe_arr_len++] == 1 && ++i)
				break ;
			else if (proc->line_expanded[i] == 32
				&& proc->space_arr[proc->space_arr_len++] == 1)
				i++;
			else
				proc->process[row][col++] = proc->line_expanded[i++];
		}
		proc->process[row][col] = '\0';
		row++;
	}
	proc->process[row] = NULL;
}

void	ft_proceniser(t_proc *proc)
{
	ft_process_count(proc);
	proc->pipe_arr_len = 0;
	proc->space_arr_len = 0;
	ft_mem_proceniser(proc);
	proc->pipe_arr_len = 0;
	proc->space_arr_len = 0;
	ft_fill_proceniser(proc);
}
