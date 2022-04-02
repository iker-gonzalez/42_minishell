/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:54:47 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/02 22:27:10 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_red_type(t_proc *proc)
{
	int	i;
	int	j;

	i = 0;
	proc->red_out_arr_len = 0;
	proc->red_in_arr_len = 0;
	proc->red_out_del_arr_len = 0;
	while ((*proc->lst)->args[i])
	{
		j = 0;
		while ((*proc->lst)->args[i][j])
		{
			if ((*proc->lst)->args[i][j] == 62)
			{
				if (ft_strlen((*proc->lst)->args[i]) > j)
				{
					if (((*proc->lst)->args[i][j + 1]) == 62 && proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
				
					ft_set_red_out_app(proc, i, j);
					j++;
				}
				else
				{
					if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
						ft_set_red_out(proc, i, j);
				}
			}
			else if ((*proc->lst)->args[i][j] == 60 && proc->red_in_arr[proc->red_in_arr_len++] == 1)
				ft_set_red_in(proc, i, j);
			j++;
		}
		i++;
	}
}
