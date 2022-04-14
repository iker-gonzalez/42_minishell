/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:45:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 19:34:30 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_int2(t_proc *proc)
{
	int i;
	
	i = -1;
	while (++i < proc->process_count)
	{
		if (proc->added_spc_arr_length[i])
			free(proc->added_spc_arr_length[i]);
	}
	free(proc->added_spc_arr_length);
}

void	ft_free_double_int(t_proc *proc, int **str)
{
	int i;
	
	i = -1;
	printf("proc count: %d\n", proc->process_count);
	while (++i < proc->process_count)
	{
		printf("MARIO\n");
		free(str[i]);
	}
	free(str);
}

void	ft_free_process(t_proc *proc)
{
	int	row;

	row = -1;
	while (++row <= proc->process_count)
	{
		if (proc->process[row])
			free(proc->process[row]);
	}
	free(proc->process);
}

void	ft_free_double_char(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		if (!str[i])
			return ;
		if (str[i])
			free(str[i]);
	}
	if (str)
		free(str);
}

void	ft_freelist(t_node *lst)
{
   t_node* tmp;

   while (lst != NULL)
    {
		printf("PEPEI\n");
       tmp = lst;
       lst = lst->next;
       free(tmp);
    }

}

void	ft_free_args_red(t_proc *proc)
{
	int	row;

	row = -1;
	while ((*proc->lst)->args_red && (*proc->lst)->args_red[++row])
	{
		if ((*proc->lst)->has_red)
			free((*proc->lst)->args_red[row]);
	}
	if ((*proc->lst)->has_red && (*proc->lst)->args_red)
		free((*proc->lst)->args_red);
}

void	ft_free_args(t_proc *proc)
{
	int	row;

	row = -1;
	while ((*proc->lst)->args[++row])
	{
		if ((*proc->lst)->args[row])
			free((*proc->lst)->args[row]);
	}
	if ((*proc->lst)->args)
		free((*proc->lst)->args);
}

void	ft_free_node_routes(t_proc *proc)
{
	free((*proc->lst)->route);
}

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
	if (proc->added_spc_arr_length)
		ft_free_double_int(proc, proc->added_spc_arr_length);
	if (proc->added_spc_arr)
		ft_free_double_int(proc, proc->added_spc_arr);
	//ft_free_process(proc);
	if (proc->process)
		ft_free_double_char(proc->process);
	//if (proc->set->paths)
	//	ft_free_double_char(proc->set->paths);
	//if (proc->aux)
	//	free(proc->aux);
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
	ft_lstiter(proc, ft_free_args_red);
	ft_lstiter(proc, ft_free_node_routes);
	//if (proc->lst)
	ft_freelist((*proc->lst));
	free(proc->lst);
	//ft_free_paths(proc);
	//
}
