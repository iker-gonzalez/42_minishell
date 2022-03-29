/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:45:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 11:31:29 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	ft_free_nodes(t_proc *proc)
{
	if (!(*proc->lst))
		return ;
    free ((*proc->lst)->content);
    free ((*proc->lst)->exp_content);
}
*/

void	ft_free_process(t_proc *proc)
{
	int	row;

	row = 0;
	while (row < proc->process_count)
	{
		free(proc->process[row]);
		row++;
	}
	free(proc->process);
}

void	ft_free_double_char(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	ft_freelist(t_node **lst)
{
	t_node	*temp;

	if (!*lst)
	{
		return ;
	}
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		free (temp);
	}
	*lst = NULL;
	free (lst);
}

void	ft_free_args(t_proc *proc)
{
	int	row;

	row = -1;
	while ((*proc->lst)->args[++row])
		free((*proc->lst)->args[row]);
	free((*proc->lst)->args);
}

void	ft_free_proc(t_proc *proc)
{
	if (proc->space_arr_len)
		free(proc->line_read);
	if (proc->space_arr_len)
		free(proc->line_expanded);
	if (proc->space_arr_len)
		free(proc->space_arr);
	if (proc->space_arr_len)
		free(proc->exp_sp_arr);
	if (proc->pipe_arr_len)
		free(proc->pipe_arr);
	if (proc->space_arr_len)
		free(proc->red_in_arr);
	if (proc->space_arr_len)
		free(proc->red_in_app_arr);
	if (proc->space_arr_len)
		free(proc->red_out_arr);
	if (proc->space_arr_len)
		free(proc->red_out_del_arr);
}

void	ft_free(t_proc *proc)
{
	ft_free_proc(proc);
	ft_free_process(proc);
	ft_lstiter(proc, ft_free_args);
	ft_freelist(proc->lst);
	//ft_free_paths(proc);
	//
}
