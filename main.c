/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:06 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/16 12:00:36 by ikgonzal         ###   ########.fr       */
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
		ft_parse_input(proc);
		ft_expand_input(proc);
		ft_tokenizer33(proc);
		//ft_gen_lst(proc);
		ft_print_val(proc);
		//ft_lstiter(proc, print_list);
	}
	return(0);
}

int main (void)
{
	t_proc proc;

	ft_memset(&proc, 0, sizeof(t_proc));
	set_up_shell(&proc);
	ft_loop(&proc);
	return(0);
}
