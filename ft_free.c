/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:45:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/22 20:29:12 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void  ft_free_process(t_proc *proc)
{
  int row;

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
	int row;

	row = -1;
	while ((*proc->lst)->args[++row])
		free((*proc->lst)->args[row]);
	free((*proc->lst)->args);
}

void	ft_free_proc(t_proc *proc)
{
	free(proc->line_read);
	free(proc->line_expanded);
	free(proc->space_arr);
	free(proc->exp_sp_arr);
	free(proc->pipe_arr);
	free(proc->red_in_arr);
	free(proc->red_in_app_arr);
	free(proc->red_out_arr);
	free(proc->red_out_del_arr);
}

void	ft_free(t_proc *proc)
{
	ft_free_proc(proc);
	ft_free_process(proc);
	ft_lstiter(proc, ft_free_args);
	ft_freelist(proc->lst);
	//ft_free_paths(proc);
}