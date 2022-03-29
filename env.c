/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:39:23 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 10:37:24 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_proc *proc, int cmd_count)
{
	int	i;

	if (cmd_count > 1)
		print_error("No such file or directory", 127);
	i = -1;
	while (proc->env[++i])
		printf("%s\n", proc->env[i]);
	return (0);
}
