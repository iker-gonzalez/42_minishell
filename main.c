/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:06 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/22 19:42:10 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_loop(t_proc *proc)
{

	while (1)
	{
		ft_read_input(proc);
		if (!ft_strncmp(proc->line_read, "exit", 4))
			exit (0);
		ft_check_errors(proc);
		ft_parse_input(proc);
		ft_expand_input(proc);
		ft_tokenizer(proc);
		ft_free(proc);
		//ft_print_val(proc);
	}
	return(0);
}

int main (void)
{
	t_proc proc;

	ft_memset(&proc, 0, sizeof(t_proc));
	set_up_shell(&proc);
	ft_loop(&proc);
	free(proc.prompt);
	return(0);
}
