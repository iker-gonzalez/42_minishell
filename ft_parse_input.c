/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:39 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/12 13:31:43 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_pipes(t_proc *proc)
{
	int	i;
	int	pipe_count;
	int	pipe_exp_len;

	i = 0;
	pipe_count = 0;
	pipe_exp_len = 0;
	while (proc->line_read[i])
	{
		if (proc->line_read[i] == 124)
			pipe_count++;
		i++;
	}
	if (pipe_count)
		proc->pipe_arr = malloc(sizeof(int) * pipe_count);
}

void	ft_parse_red_in(t_proc *proc)
{
	int	i;

	i = 0;
	while (proc->line_read[i])
	{
		if (proc->line_read[i] == 60 && proc->line_read[i + 1] == 60)
		{
			proc->red_in_app_count++;
			i++;
		}
		else if (proc->line_read[i] == 60 && proc->line_read[i + 1] != 60)
			proc->red_in_count++;
		i++;
	}
	if (proc->red_in_count)
		proc->red_in_arr = malloc(sizeof(int)
				* proc->red_in_count + sizeof(int));
	if (proc->red_in_app_count)
		proc->red_in_app_arr = malloc (sizeof(int)
				* proc->red_in_app_count + sizeof(int));
}

void	ft_parse_red_out(t_proc *proc)
{
	int	i;

	i = 0;
	while (proc->line_read[i])
	{
		if (proc->line_read[i] == 62 && proc->line_read[i + 1] == 62)
		{
			proc->red_out_del_count++;
			i++;
		}
		else if (proc->line_read[i] == 62 && proc->line_read[i + 1] != 62)
			proc->red_out_count++;
		i++;
	}
	if (proc->red_out_count)
		proc->red_out_arr = malloc(sizeof(int) * proc->red_out_count);
	if (proc->red_out_del_count)
		proc->red_out_del_arr = malloc (sizeof(int) * proc->red_out_del_count);
}

void	ft_parse_spaces(t_proc *proc)
{
	int	i;

	i = 0;
	while (proc->line_read[i])
	{
		if (proc->line_read[i] == 32)
			proc->space_count++;
		i++;
	}
	if (proc->space_count)
		proc->space_arr = malloc (sizeof(int) * proc->space_count);
}

void	ft_parse_input(t_proc *proc)
{
	ft_parse_pipes(proc);
	ft_parse_red_in(proc);
	ft_parse_red_out(proc);
	ft_parse_spaces(proc);
}
