/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:33:38 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/11 19:40:04 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"

void	ft_set_red_write(int fd)
{
	dup2(fd, 1);
	close(fd);
}

void	ft_set_red_out(t_proc *proc, int i)
{
	if ((*proc->lst)->outfd)
		close((*proc->lst)->outfd);
	(*proc->lst)->outfd = open((*proc->lst)->args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if ((*proc->lst)->outfd < 0)
		printf("Error al crear el fd para outfile");
}
