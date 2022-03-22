/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:45:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/22 11:06:45 by ikgonzal         ###   ########.fr       */
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

void	ft_freelist(t_node **head)
{
	t_node	*temp;

	if (!*head)
	{
		return ;
	}
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free (temp);
	}
	*head = NULL;
}

void  ft_free_args(t_proc *proc, char **args)
{
  int row;

  row = 0;
  while (row < proc->row_len)
  {
    free(args[row]);
    row++;
  }
  free(args);
}