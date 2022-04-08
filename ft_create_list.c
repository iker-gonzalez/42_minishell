/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:48 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/08 20:24:58 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_node	*ft_new_node(char **args)
{
	t_node	*ret;
	int		i;

	ret = malloc(sizeof (t_node));
	memset(ret, 0, sizeof(t_node));
	if (!ret)
		return (NULL);
	i = 0;
	while (args[i])
		i++;
	ret->args = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (args[++i])
		ret->args[i] = ft_strdup(args[i]);
	ret->args[i] = NULL;
	return (ret);
}

void	ft_add_node_back(t_proc *proc, t_node **node, t_node *new)
{
	if (*node)
	{
		proc->head = *node;
		while ((*node)->next)
			(*node) = (*node)->next;
		new->previous = *node;
		(*node)->next = new;
		(*node) = proc->head;
	}
	else
		(*node) = new;
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
