/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_fds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/03/23 19:57:48 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ft_find_redi(t_proc *proc)
{
	
}

void	ft_process_fds(t_proc *proc)
{
	ft_lstiter(proc, ft_find_redi);
}



/*int	p[2];

	if (proc->lst->previous == NULL && proc->lst->next == NULL)
	{
		proc->lst->fd[0] = 0;
		pproc->lst->fd[1] = 1;
	}
	else if (proc->lst->previous == NULL && proc->lst->next != NULL)
	{
		pipe(p);
		proc->lst->fd[0] = 0;
		proc->lst->fd[1] = p[0]
	}
*/
