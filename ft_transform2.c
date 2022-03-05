/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:37:59 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/04 14:08:29 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rmv_dollar(t_node *node)
{
	int	i;
	int	k;

	if ((ft_count_char(node, 36)) == 1)
	{
		node->exp_content = malloc(sizeof(char) * ft_strlen(node->content));
		i = 0;
		k = 0;
		while (node->content[i++] != 36)
			node->exp_content[i] = node->content[i];
		if(!node->single_quoted)
		{
			i++;
			node->exp_content[i] = node->content[i];
		}
	}
}

int	ft_count_tquotes(t_node *node)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while(node->content[i])
	{
		if (node->content[i] == 39 && node->content[i + 1] == 34)
		{
			k++;
			i++;
		}
		else if (node->content[i] == 34 && node->content[i + 1] == 39)
		{
			k++;
			i++;
		}
		i++;
	}
	if(node->content[i] == 39 && node->content[i + 1] == 34)
		k++;
	else if(node->content[i] == 34 && node->content[i + 1] == 39)
		k++;
	return(k);
}

int	ft_determine(t_node *node, int i)
{
	int ret;
	
	while(node->content[i])
	{
		if (node->content[i] == 39)
			ret = 1;
		else if (node->content[i] == 34)
			ret = 2;
		i++;
	}
	return (ret);
}

int	ft_determine_scope(t_node *node)
{
	int	i;
	int scope;
	
	i = 0;
	scope = 0;
	if (node->triple_quoted)
	{
		while (node->content[i] && node->content[i] != 34 && node->content[i] != 39)
			i++;
		if (node->content[i] == 39)
			scope = 1 + (ft_determine(node, i));
		else if (node->content[i] == 34)
			scope = 2 + (ft_determine(node, i));
	}
	return (scope);
}

void	ft_odd_snode(t_node *node)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (node->content[i])
	{
		if (node->content[i] == 39 || node->content[i] == 34)
			i++;
		else
			node->exp_content[k++] = node->content[i++];
	}
	node->exp_content[k] = '\0';
}

void	ft_odd_scope(t_node *node)
{
	int i;
	int k;
	
	if (!node->next)
		ft_odd_snode(node);
	else
	{
		i = 0;
		k = 0;
		while (node->content[i])
		{
			if (node->content[i] == 39)
				i++;
			else if (node->content[i] == 34)
				i++;
			else
				node->exp_content[k++] = node->content[i++];
		}
		node->exp_content[k] = '\0';
	}
}

void	ft_rmv_snode_tquotes(t_node *node)
{
	int i;
	int k;
	int scope;
	
	i = 0;
	k = 0;
	if (node->triple_quoted)
	{
		node->exp_content = malloc(sizeof(char) * ft_strlen(node->content));
		scope = ft_determine_scope(node);
		while (node->content[i] && (scope == 2 || scope == 4))
		{
			if (node->content[i] == 34 && scope == 4)
				i++;
			else if (node->content[i] == 39 && scope == 2)
				i++;
			else
				node->exp_content[k++] = node->content[i++];	
			node->exp_content[k] = '\0';
		}
		if (scope != 2 && scope != 4)
			ft_odd_scope(node);
	}
}

