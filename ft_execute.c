/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:44 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/31 18:34:15 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	ft_execute_command(t_set *set, char *route, char **args)
{
	execve(route, args, set->env);
}

void	ft_cmd_exist(t_proc *proc, t_set *set)
{
	int		i;

	i = 0;
	while (set->paths[i])
	{
		set->paths[i] = ft_strjoin(set->paths[i], (*proc->lst)->args[0]);
		if (access(set->paths[i], F_OK) == 0)
		{
			printf("%s\n", set->paths[i]);
			ft_execute_command(set, set->paths[i], (*proc->lst)->args);
		}
		i++;
	}
}

void	ft_check_builtins(t_proc *proc, t_set *set)
{
	if ((ft_strncmp_len((*proc->lst)->args[0], "env", 3)) == 0)
		ft_env(set, ft_count_argc((*proc->lst)->args));
	else if ((ft_strncmp_len((*proc->lst)->args[0], "pwd", 3)) == 0)
		ft_pwd();
	else if ((ft_strncmp_len((*proc->lst)->args[0], "cd", 2)) == 0)
		ft_cd((*proc->lst)->args, set);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "export", 6)) == 0)
		export(set, (*proc->lst)->args);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "unset", 5)) == 0)
		unset(set, (*proc->lst)->args);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "exit", 4)) == 0)
		ft_exit((*proc->lst)->args);
	else if ((ft_strncmp_len((*proc->lst)->args[0], "?", 1)) == 0)
		printf("%d", errno);
	//else if ((ft_strncmp((*proc->lst)->args[0], "echo", 4)) == 0)
			//echo();
}

void	ft_execute(t_proc *proc, t_set *set)
{
	ft_check_builtins(proc, set);
	//ft_cmd_exist(proc);
}



/*
//Creates double char eliminating the nodes that became empty after being transformed. 
//
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
