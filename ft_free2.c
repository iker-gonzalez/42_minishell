/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:09:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/14 13:01:02 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_int2(t_proc *proc)
{
	int	i;

	i = -1;
	while (++i < proc->process_count)
	{
		if (proc->added_spc_arr_length[i])
			free(proc->added_spc_arr_length[i]);
	}
	free(proc->added_spc_arr_length);
}

void	ft_free_double_int(t_proc *proc)
{
	int	i;

	i = -1;
	while (++i < proc->process_count)
	{
		if (proc->added_spc_arr[i])
			free(proc->added_spc_arr[i]);
	}
	free(proc->added_spc_arr);
}

void	ft_free_process(t_proc *proc)
{
	int	row;

	row = -1;
	while (++row < proc->process_count)
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
