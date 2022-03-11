/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:48 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/11 17:05:57 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void print_list (t_proc *proc)
{
		printf("content: %s\n", (*proc->lst)->content);
		printf("exp_content: %s\n", (*proc->lst)->exp_content);
		printf("exp_len: %d\n", (*proc->lst)->exp_len);
		//printf("is_empty: %d\n", (*proc->lst)->is_empty);
		/*printf("single_quoted: %d\n", (*proc->lst)->single_quoted);
		printf("double_quoted: %d\n", (*proc->lst)->double_quoted);
		printf("triple_quoted: %d\n", (*proc->lst)->triple_quoted);
		printf("pipe: %d\n", (*proc->lst)->pipe);
		printf("dollar: %d\n", (*proc->lst)->dollar);
		printf("dollar_exit: %d\n", (*proc->lst)->dollar_exit);
		printf("red_in: %d\n", (*proc->lst)->red_in);
		printf("red_in_append: %d\n", (*proc->lst)->red_in_append);
		printf("red_out: %d\n", (*proc->lst)->red_out);
		printf("red_out_del: %d\n", (*proc->lst)->red_out_del);*/
		//printf("previous: %p\n", (*proc->lst)->previous);
		//printf("next: %p\n", (*proc->lst)->next);
		proc = NULL;
		printf("==============================\n");
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