/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:37:59 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/05 14:01:47 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_trm_dollar(t_node *node, int *i)
{
	char *str;
	char *env;
	int k;

	k = 0;
	str = malloc(sizeof(char) * ft_strlen(node->content) + 1);
	while (node->content[*i])
	{
		if (node->content[*i] != 20 && node->content[*i] != 36 
			&& node->content[*i] != 45 && node->content[*i] != 34 && node->content[*i] != 39)
			str[k++] = node->content[*i];
		*i += 1;
	}
	str[k] = '\0';
	printf("str: %s\n", str);
	env = getenv(str);
	printf("%s", env);
}
