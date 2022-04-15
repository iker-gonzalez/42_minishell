/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:21:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/15 13:23:14 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

void	ft_parental_wait(t_proc *proc)
{
	int		stt;
	pid_t	process;

	stt = 0;
	process = waitpid((*proc->lst)->pid, &stt, 0);
	if (WIFEXITED(stt))
		g_exit_status = WEXITSTATUS(stt);
}

void	ft_is_built_in(t_node *node, int index)
{
	if ((ft_strncmp_len(node->args[index], "env", 3)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "pwd", 3)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "cd", 2)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "export", 6)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "unset", 5)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "exit", 4)) == 0)
		node->is_built_in = 1;
	else if ((ft_strncmp_len(node->args[index], "echo", 4)) == 0)
		node->is_built_in = 1;
	else
		node->is_built_in = 0;
}

void	ft_set_process_type(t_proc *proc)
{
	if ((*proc->lst)->args[0][0] != 60 && (*proc->lst)->args[0][0] != 62)
		ft_is_built_in((*proc->lst), 0);
	else
		ft_is_built_in((*proc->lst), 2);
}

void	ft_launch_process(t_proc *proc)
{
	ft_redirection_set_up(proc);
	ft_lstiter(proc, ft_check_if_red);
	ft_lstiter(proc, ft_set_process_type);
	ft_redirection_set_up(proc);
	ft_lstiter(proc, ft_set_args_red);
	ft_lstiter(proc, ft_create_children);
	ft_lstiter(proc, ft_parental_wait);
}
