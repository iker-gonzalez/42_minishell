/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:03:22 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/02/24 10:56:47 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rmv_squotes(t_node *node)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (node->content[i])
	{
		if(node->content[i] == 39 && !node->double_quoted)
			k++;
		i++;
	}
	node->exp_content = malloc(sizeof(char) * ft_strlen(node->content) - k + 1);
	i = 0;
	k = 0;
	while (node->content[i])
	{
		if(node->content[i] == 39 && !node->double_quoted)
			i++;
		else
			node->exp_content[k++] = node->content[i++];
	}
	node->exp_content[k] = '\0';
}

void	ft_lstiter(t_proc *proc, void (*f)(t_node *))
{
	if (!f)
	{
		printf("Error");
		return ;
	}
	while ((*proc->lst))
	{
		f((*proc->lst));
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head; 
}