/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:44 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/25 13:36:06 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_command(t_proc *proc, char *route, char **args)
{
	execve(route, args, proc->env);
}

void	ft_cmd_exist(t_proc *proc)
{
	int		i;

	i = 0;
	while (proc->paths[i])
	{
		proc->paths[i] = ft_strjoin(proc->paths[i], (*proc->lst)->args[0]);
		if (access(proc->paths[i], F_OK) == 0)
		{
			printf("%s\n", proc->paths[i]);
			ft_execute_command(proc, proc->paths[i], (*proc->lst)->args);
		}
		i++;
	}
}

void	ft_check_builtins(t_proc *proc)
{
	if ((ft_strncmp((*proc->lst)->args[0], "env", 3)) == 0)
		ft_env(proc);
	else if ((ft_strncmp((*proc->lst)->args[0], "pwd", 3)) == 0)
		ft_pwd();
	else if ((ft_strncmp((*proc->lst)->args[0], "cd", 2)) == 0)
		ft_cd((*proc->lst)->args, proc);
	else if ((ft_strncmp((*proc->lst)->args[0], "export", 6)) == 0)
	{
		export(proc, (*proc->lst)->args);
		//ft_env(proc);
	}
	
	//else if ((ft_strncmp((*proc->lst)->args[0], "echo", 4)) == 0)
		//echo();
}

void	ft_execute(t_proc *proc)
{
	ft_check_builtins(proc);
	//ft_cmd_exist(proc);
}




//Creates double char eliminating the nodes that became empty after being transformed. 
/*
void	ft_test(t_proc *proc)
{
	int k;

	k = 0;
	while(*proc->lst)
	{
		if((*proc->lst)->is_empty)
			k++;
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
	proc->line_expanded = malloc(sizeof(char *) * (proc->node_count - k + 1));
	k = 0;
	while(*proc->lst)
	{
		proc->line_expanded[k] = malloc(sizeof(char) * ft_strlen((*proc->lst)->content) + 1);
		if(!(*proc->lst)->is_empty)
			proc->line_expanded[k++] = (*proc->lst)->content;
		(*proc->lst) = (*proc->lst)->next;
	}
	proc->line_expanded[k] = NULL;
	(*proc->lst) = proc->head;
}
*/
