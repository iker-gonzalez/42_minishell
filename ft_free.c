/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:45:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/16 13:34:03 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_safe_path(t_set *set)
{
	int	i;

	i = -1;
	while (set->safe_paths[++i])
		free(set->safe_paths[i]);
	free(set->safe_paths);
}

void	ft_free_double_int(t_proc *proc, int **str)
{
	int	i;

	i = -1;
	while (++i < proc->process_count)
	{
		free(str[i]);
	}
	free(str);
}

void	ft_free_proc(t_proc *proc)
{
	if (proc->line_read)
		free(proc->line_read);
	if (proc->line_expanded)
		free(proc->line_expanded);
	if (proc->space_arr)
		free(proc->space_arr);
	if (proc->exp_sp_arr)
		free(proc->exp_sp_arr);
	if (proc->pipe_arr)
		free(proc->pipe_arr);
	if (proc->red_in_arr)
		free(proc->red_in_arr);
	if (proc->red_in_app_arr)
		free(proc->red_in_app_arr);
	if (proc->red_out_arr)
		free(proc->red_out_arr);
	if (proc->red_out_del_arr)
		free(proc->red_out_del_arr);
	if (proc->added_spc_arr_length)
		ft_free_double_int(proc, proc->added_spc_arr_length);
	if (proc->added_spc_arr)
		ft_free_double_int(proc, proc->added_spc_arr);
	if (proc->process)
		ft_free_double_char(proc->process);
}

void	ft_free_set(t_set *set)
{
	if (set->env)
		ft_free_double_char(set->env);
}

void	ft_free(t_proc *proc)
{
	ft_free_proc(proc);
	ft_lstiter(proc, ft_free_args);
	ft_lstiter(proc, ft_free_args_red);
	ft_lstiter(proc, ft_free_node_routes);
	ft_freelist((*proc->lst));
	free(proc->lst);
}
