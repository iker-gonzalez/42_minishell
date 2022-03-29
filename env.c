/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:39:23 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 13:47:51 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_set *set, int cmd_count)
{
	int	i;

	if (cmd_count > 1)
		print_error("No such file or directory", 127);
	i = -1;
	while (set->env[++i])
		printf("%s\n", set->env[i]);
	return (0);
}
