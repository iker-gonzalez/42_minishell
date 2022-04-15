/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:33 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 14:12:49 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_input(t_proc *proc)
{
	proc->line_read = readline(proc->prompt);
	listen_signals_daddy();
	add_history(proc->line_read);
}

void	get_prompt(t_proc *proc)
{
	proc->prompt = "@papa$hell: ";
}

void	ft_create_terminal(t_proc *proc)
{
	get_prompt(proc);
	ft_read_input(proc);
}
