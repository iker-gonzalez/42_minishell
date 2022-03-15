/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:06 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/15 12:33:55 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_loop(t_proc *proc)
{
	int	ms_on;

	ms_on = 1;
	while (ms_on)
	{
		ft_read_input(proc);
		if (!ft_strncmp(proc->line_read, "exit", 4))
			exit (0);
		ft_parse_input(proc);
		ft_expand_input(proc);
		ft_arrange_input(proc);
	}
	return(0);
}

int main (void)
{
	t_proc proc;

	ft_memset(&proc, 0, sizeof(t_proc));
	set_up_shell(&proc);
	ft_loop(&proc);
	ft_free_double_char((&proc)->paths);
	return(0);
}
