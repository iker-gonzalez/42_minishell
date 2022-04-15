/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:06:50 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/15 20:30:26 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_system(t_node *node, t_proc *proc)
{
	int	index;

	index = 0;
	if ((*proc->lst)->args[0][0] == 60 || (*proc->lst)->args[0][0] == 62)
		index = 2;
	ft_set_route(proc, (*proc->lst)->args[index]);
	if (proc->infile)
		exit(proc->infile);
	if (node->route == NULL && !proc->no_cmd)
		print_error(": command not found", 127, node->args[index], 1);
	if (node->has_red)
		execve(node->route, node->args_red, proc->set->env);
	else
		execve(node->route, node->args, proc->set->env);
	exit(0);
}

void	ft_child_conditions(int *lpipe, int *rpipe, t_node *node, t_proc *proc)
{
	if (lpipe)
		ft_set_read(lpipe);
	if (rpipe)
		ft_set_write(rpipe);
	if (node->outfd)
		ft_set_red_write(node->outfd);
	if (node->infd)
		ft_set_red_read(node->infd);
	if (node->is_built_in)
	{
		if (node->has_red)
			ft_check_builtins(proc, node, 1, node->args_red);
		else
			ft_check_builtins(proc, node, 1, node->args);
	}
	else
		ft_exec_system(node, proc);
}

void	ft_create_child(int *lpipe, int *rpipe, t_node *node, t_proc *proc)
{
	listen_signals_child();
	node->pid = fork();
	if (node->pid < 0)
		perror("fork failed");
	if (node->pid == 0)
		ft_child_conditions(lpipe, rpipe, node, proc);
}

void	ft_create_children(t_proc *proc)
{
	if ((*proc->lst)->previous == NULL && (*proc->lst)->next == NULL)
		ft_case_only_child(proc);
	else if ((*proc->lst)->previous == NULL && (*proc->lst)->next != NULL)
		ft_case_first_of_many(proc);
	else if ((*proc->lst)->previous != NULL && (*proc->lst)->next == NULL)
		ft_case_last_of_many(proc);
	else
		ft_case_middle_guy(proc);
}

void	ft_check_builtins(t_proc *proc, t_node *node, int child, char **args)
{
	if ((ft_strncmp_len(args[0], "env", 3)) == 0)
		ft_env(proc, ft_count_argc(args), child, node->outfd);
	else if ((ft_strncmp_len(args[0], "pwd", 3)) == 0)
		ft_pwd(child, node->outfd);
	else if ((ft_strncmp_len(args[0], "cd", 2)) == 0)
		ft_cd(args, proc->set, child);
	else if ((ft_strncmp_len(args[0], "export", 6)) == 0)
		export(proc, args, child, node->outfd);
	else if ((ft_strncmp_len(args[0], "unset", 5)) == 0)
		unset(proc->set, args, child);
	else if ((ft_strncmp_len(args[0], "exit", 4)) == 0)
		ft_exit(args, child, proc->set, proc);
	else if ((ft_strncmp_len(args[0], "echo", 4)) == 0)
		ft_echo(args, (*proc->lst)->outfd, child);
}
