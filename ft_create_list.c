/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:48 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/05 11:58:36 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void print_list (t_node **lst)
{
	while (*lst)
	{
		printf("content: %s\n", (*lst)->content);
		printf("exp_content: %s\n", (*lst)->exp_content);
		printf("exp_len: %d\n", (*lst)->exp_len);
		printf("is_empty: %d\n", (*lst)->is_empty);
		printf("single_quoted: %d\n", (*lst)->single_quoted);
		printf("double_quoted: %d\n", (*lst)->double_quoted);
		printf("triple_quoted: %d\n", (*lst)->triple_quoted);
		printf("pipe: %d\n", (*lst)->pipe);
		printf("dollar: %d\n", (*lst)->dollar);
		printf("dollar_exit: %d\n", (*lst)->dollar_exit);
		printf("red_in: %d\n", (*lst)->red_in);
		printf("red_in_append: %d\n", (*lst)->red_in_append);
		printf("red_out: %d\n", (*lst)->red_out);
		printf("red_out_del: %d\n", (*lst)->red_out_del);
		printf("previous: %p\n", (*lst)->previous);
		printf("next: %p\n", (*lst)->next);
		printf("==============================\n");
		*lst = (*lst)->next;
	}
}

void ft_gen_lst(t_proc *proc)
{
	int i;

	proc->tokens = ft_split(proc->line_read, ' ');
	i = 0;
	while (proc->tokens[i])
		i++;
	proc->node_count = i;
	proc->lst = malloc(sizeof(t_node) * proc->node_count);
	ft_memset((proc->lst), 0, sizeof(t_node *));
	i = 0;
	while (proc->tokens[i])
	{
		ft_add_node_back(proc->lst, ft_new_node(proc->tokens[i]));
		i++;
	}
	proc->head = (*proc->lst);
}

t_node	*ft_new_node(char *content)
{
	t_node *ret;

	ret = malloc(sizeof (t_node));
	memset(ret, 0, sizeof(t_node));
	if (!ret)
		return NULL;
	ret->content = content;
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
