/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:48 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/15 11:36:30 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void ft_gen_lst(t_proc *proc)
{
	int i;
	char **args;

	/*proc->tokens = ft_split(proc->line_read, ' ');
	i = 0;
	while (proc->tokens[i])
		i++;
	proc->node_count = i;*/
	proc->lst = malloc(sizeof(t_node) * proc->token_count);
	ft_memset((proc->lst), 0, sizeof(t_node *));
	i = 0;
	while (i < proc->process_count)
	{
		args = ft_split(proc->process[i], ' ');
		ft_add_node_back(proc->lst, ft_new_node(args));
		i++;
	}
	proc->head = (*proc->lst);
}

t_node	*ft_new_node(char **args)
{
	t_node *ret;

	ret = malloc(sizeof (t_node));
	memset(ret, 0, sizeof(t_node));
	if (!ret)
		return NULL;
	ret->args = args;
	return (ret);
}

void	ft_add_node_back(t_node **node, t_node *new)
{
	t_node *head;

	if (*node)
	{
		head = *node;
		while((*node)->next)
			(*node) = (*node)->next;
		new->previous = *node;
		(*node)->next = new;
		(*node) = head;
	}
	else
		(*node) = new;
}
