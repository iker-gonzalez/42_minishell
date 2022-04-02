/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:39:23 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/02 10:38:21 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_proc *proc, int cmd_count, int child)
{
	int	i;

	if (cmd_count > 1)
		print_error(": No such file or directory", 127, (*proc->lst)->args[1], proc->set);
	i = -1;
	while (proc->set->env[++i])
		printf("%s\n", proc->set->env[i]);
	if (child)
		exit (0);
	return (0);
}
