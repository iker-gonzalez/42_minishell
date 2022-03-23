/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:44 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/23 12:24:52 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void ft_execute_command(t_proc *proc, char *route, int processid)
{
	char **arg;
	char *env;
	
	if (proc->cmd_count > 1)
		arg = ft_split(proc->process[processid], ' ');
	else
		arg = ft_split(proc->line_read, ' ');
	env = NULL;
	execve(route, arg, &env);
}

void	ft_cmd_exist(t_proc *proc, char *token, int processid)
{
	int		i;

	i = 0;
	proc->cmd_found = 0;
	while (proc->paths[i])
	{
		proc->paths[i] = ft_strjoin(proc->paths[i], token);
		if (access(proc->paths[i], F_OK) == 0)
		{
			proc->cmd_found = 1;
			ft_execute_command(proc, proc->paths[i], processid);
		}
		i++;
	}
}
*/
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

void	ft_print_line(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		printf("token %d:", i);
		printf("%s \n", line[i]);
		i++;
	}
}*/
