/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out_app_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:01:50 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/15 19:24:00 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

void	ft_set_red_out_app(t_proc *proc, int i)
{
	if ((*proc->lst)->outfd)
		close((*proc->lst)->outfd);
	(*proc->lst)->outfd = open((*proc->lst)->args[i + 1],
			O_WRONLY | O_APPEND | O_CREAT, 0777);
	if ((*proc->lst)->outfd < 0)
		printf("Error al crear el fd para outfile");
}
