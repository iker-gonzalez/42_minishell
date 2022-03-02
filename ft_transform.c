/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:03:22 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/02 19:13:22 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_char(t_node *node, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (node->content[i])
	{
		if (c == 39)
		{
			if(node->content[i] == 39 && !node->double_quoted)
				k++;
		}
		else if (c == 34)
		{
			if(node->content[i] == 34 && !node->single_quoted)
				k++;
		}
		i++;
	}
	return (k);
}

void	ft_rmv_squotes(t_node *node)
{
	int	i;
	int	k;

	k = ft_count_char(node, 39);
	node->exp_content = malloc(sizeof(char) * ft_strlen(node->content) - k + 1);
	i = 0;
	k = 0;
	while (node->content[i])
	{
		if(node->content[i] == 39 && !node->double_quoted)
		{
			if(ft_strlen(node->content) == 1)
				node->is_empty = 1;
			i++;
		}
		else 
			node->exp_content[k++] = node->content[i++];
	}
	node->exp_content[k] = '\0';
	node->content = node->exp_content;
}

void	ft_rmv_dquotes(t_node *node)
{
	int	i;
	int	k;

	k = ft_count_char(node, 34);
	node->exp_content = malloc(sizeof(char) * ft_strlen(node->content) - k + 1);
	i = 0;
	k = 0;
	while (node->content[i])
	{
		if(node->content[i] == 34 && !node->single_quoted)
		{
			if(ft_strlen(node->content) == 1)
				node->is_empty = 1;
			i++;
		}
		else
			node->exp_content[k++] = node->content[i++];
	}
	node->exp_content[k] = '\0';
	node->content = node->exp_content;
}

void	ft_lstiter(t_proc *proc, void (*f)(t_node *))
{
	if (!f)
		return ;
	while ((*proc->lst))
	{
		f((*proc->lst));
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head; 
}

void	ft_transform_input(t_proc *proc)
{
    ft_lstiter(proc, ft_rmv_squotes);
    ft_lstiter(proc, ft_rmv_dquotes);
	ft_lstiter(proc, ft_rmv_dollar);
	ft_test(proc);
    print_list(proc->lst);
	ft_print_line(proc->line_expanded);
}