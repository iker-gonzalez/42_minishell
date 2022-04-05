/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:33 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/05 12:27:19 by ikgonzal         ###   ########.fr       */
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
	char	*user;
	char	*logo;

	//if (!USER)
		//user = strdup("user");
	user = getenv("USER");
	logo = "@papa$hell: ";
	proc->prompt = ft_strjoin(user, logo);
}
void	ft_create_terminal(t_proc *proc)
{
	
	get_prompt(proc);
	ft_read_input(proc);
	//ft_exit_status(proc);
}

/*
void	ft_exit_status(t_proc *proc)
{
	char *exit_status;
	char *var;
	int i;
	int edit;

	exit_status = ft_itoa(proc->set->exit_status);
	var = malloc(sizeof(char) * 2 + 1);
	var[0] = '?';
	var[1] = '=';
	var[2] = '\0';
	var = ft_strjoin(var, exit_status);
	i = -1;
	edit = 0;
	while (proc->set->env[++i])
	{
		if (((ft_strncmp(proc->set->env[i], var, 1)) == 0)
			&& ++edit)
			edit_var(proc->set, var);
	}
	if (!edit)
		proc->set->env = add_var(proc->set, var);
}
*/

