/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_args_red.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:39:34 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/15 20:30:39 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_args_red(t_proc *proc, char *arg, int *i, int *k)
{
	if (arg[0] == 62 && arg[1] != 62
		&& proc->red_out_arr_len < proc->red_out_count
		&& proc->red_out_arr[proc->red_out_arr_len++] == 1)
		*i = *i + 1;
	else if (arg[0] == 60 && arg[1] != 60
		&& proc->red_in_arr_len < proc->red_in_count
		&& proc->red_in_arr[proc->red_in_arr_len++] == 1)
		*i = *i + 1;
	else if (arg[0] == 62 && arg[1] == 62
		&& proc->red_out_del_arr_len < proc->red_out_del_count
		&& proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
		*i = *i + 1;
	else if (arg[0] == 60 && arg[1] == 60
		&& proc->red_in_app_arr_len < proc->red_in_app_count
		&& proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
		*i = *i + 1;
	else
	{
		(*proc->lst)->args_red[*k] = ft_strdup(arg);
		*k = *k + 1;
	}
}

void	ft_set_args_red(t_proc *proc)
{
	int	i;
	int	k;

	if (!(*proc->lst)->has_red)
		return ;
	i = 0;
	k = 0;
	while ((*proc->lst)->args[i])
		i++;
	(*proc->lst)->args_red = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while ((*proc->lst)->args[i])
	{
		ft_args_red(proc, (*proc->lst)->args[i], &i, &k);
		i++;
	}
	(*proc->lst)->args_red[k] = NULL;
	if (!(*proc->lst)->args_red[k])
		proc->no_cmd = 1;
}
