/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:37:59 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/02/24 14:02:05 by ikgonzal         ###   ########.fr       */
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