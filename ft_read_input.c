/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:33 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/10 11:32:37 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_input(t_proc *proc)
{
	proc->line_read = readline(proc->prompt);
	g_sig.act_child = 0;
	add_history(proc->line_read);
}

void	get_prompt(t_proc *proc)
{
	//char	*user;
	//char	*logo;

	//if (!USER)
		//user = strdup("user");
	//user = getenv("USER");
	//logo = "@papa$hell: ";
	proc->prompt = "@papa$hell: "; // cambiar user
}
void	ft_create_terminal(t_proc *proc)
{
	
	get_prompt(proc);
	ft_read_input(proc);
}

