/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:12:43 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/14 13:02:16 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_args_red(t_proc *proc)
{
	int	row;

	row = -1;
	while ((*proc->lst)->args_red && (*proc->lst)->args_red[++row])
	{
		if ((*proc->lst)->has_red)
			free((*proc->lst)->args_red[row]);
	}
	if ((*proc->lst)->args_red)
		free((*proc->lst)->args_red);
}

void	ft_free_args(t_proc *proc)
{
	int	row;

	row = -1;
	while ((*proc->lst)->args[++row])
	{
		if ((*proc->lst)->args[row])
			free((*proc->lst)->args[row]);
	}
	if ((*proc->lst)->args)
		free((*proc->lst)->args);
}

void	ft_free_node_routes(t_proc *proc)
{
	free((*proc->lst)->route);
}
