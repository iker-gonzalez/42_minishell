/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:45:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 13:23:09 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_path(t_set *set)
{
	int	i;

	i = -1;
	while (set->paths[++i])
		free(set->paths[i]);
	free(set->paths);
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
}

void	ft_free_set(t_set *set)
{
	if (set->env)
		ft_free_double_char(set->env);
	if (set->paths)
		ft_free_path(set);
}

void	ft_free(t_proc *proc)
{
	ft_free_proc(proc);
	ft_lstiter(proc, ft_free_args);
	ft_lstiter(proc, ft_free_node_routes);
	if (proc->lst)
		ft_freelist(proc->lst);
	ft_free_double_int(proc);
	ft_free_double_int2(proc);
}
