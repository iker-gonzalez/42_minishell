/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:48 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 16:35:47 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_node	*ft_new_node(char **args)
{
	t_node	*node;
	int		i;

	node = malloc(sizeof (t_node));
	memset(node, 0, sizeof(t_node));
	i = 0;
	while (args[i])
		i++;
	node->args = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (args[++i])
		node->args[i] = ft_strdup(args[i]);
	node->args[i] = NULL;
	return (node);
}

void	ft_add_node_back(t_proc *proc, t_node **lst, t_node *new)
{
	if (*lst)
	{
		proc->head = *lst;
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		new->previous = *lst;
		(*lst)->next = new;
		(*lst) = proc->head;
	}
	else
		(*lst) = new;
}

void	ft_lstiter(t_proc *proc, void (*f)(t_proc *))
{
	if (!f || proc->lst == NULL)
		return ;
	while ((*proc->lst))
	{
		f((proc));
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}
