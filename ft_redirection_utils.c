/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:54:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/10 14:43:19 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirection_set_up(t_proc *proc)
{
	proc->red_out_arr_len = 0;
	proc->red_in_arr_len = 0;
	proc->red_out_del_arr_len = 0;
	proc->red_in_app_arr_len = 0;
	proc->added_spc = 0;
	proc->added_spc_arr_len = 0;
}

void	ft_check_red_out_type(t_proc *proc, int i, int j)
{
	if (ft_strlen((*proc->lst)->args[i]) > j)
	{
		if (ft_strlen((*proc->lst)->args[i]) == 2)
		{
			if (proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
			{
				ft_set_red_out_app(proc, i);
				(*proc->lst)->has_red = 1;
			}
			j++;
		}
		else
		{
			if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
			{
				ft_set_red_out(proc, i);
				(*proc->lst)->has_red = 1;
			}
		}
	}
}

void	ft_check_red_in_type(t_proc *proc, int i, int j)
{
	if (ft_strlen((*proc->lst)->args[i]) > j)
	{
		if (((*proc->lst)->args[i][j + 1]) == 60 && proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
		{
			//ft_set_red_in_del(proc, i, j++); //here there will be the heredoc ft
			printf("heredoc");
			(*proc->lst)->has_red = 1;
		}
		else
		{
			if (proc->red_in_arr[proc->red_in_arr_len++] == 1)
			{
				ft_set_red_in(proc, i);
				(*proc->lst)->has_red = 1;
			}
		}
	}
}

void	ft_check_red_type(t_proc *proc)
{
	int	i;
	int	j;

	i = 0;
	ft_redirection_set_up(proc);
	(*proc->lst)->has_red = 0;
	ft_red_count((*proc->lst)->args);
	while ((*proc->lst)->args[i])
	{
		j = 0;
		while ((*proc->lst)->args[i][j])
		{
			if ((*proc->lst)->args[i][j] == 62)
				ft_check_red_out_type(proc, i, j);
			else if ((*proc->lst)->args[i][j] == 60)
				ft_check_red_in_type(proc, i, j);
			j++;
		}
		i++;
	}
}

int	ft_red_count(char **args)
{
	int i;
	int k;
	int red;

	i = -1;
	red = 0;
	while (args[++i])
	{
		k = 0;
		while (args[i][k])
		{
			if (args[i][k] == '>' || args[i][k] == '<')
				red++;
			k++;
		}
	}
	return (red);
}
