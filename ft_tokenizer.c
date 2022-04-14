/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 15:08:36 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_row(t_proc *proc, int *sp_len, int i)
{
	int	count_y;
	int	j;

	j = -1;
	count_y = 1;
	while (proc->process[i][++j])
	{
		if (proc->process[i][j] == 32)
		{
			if (proc->added_spc_arr_len < proc->added_spc_arr_length[i][0]
			&& proc->added_spc_arr[i][proc->added_spc_arr_len] == j)
			{
				proc->added_spc_arr_len++;
				count_y++;
			}
			else if (*sp_len < proc->exp_space_count
				&& proc->exp_sp_arr[*sp_len] == 2)
			{
				count_y++;
				*sp_len += 1;
			}
			else
				*sp_len += 1;
		}
	}
	return (count_y);
}

int	ft_count_col(t_proc *proc, int i, int *j, int *sp_len)
{
	int	col;
	int	lock;

	col = 0;
	lock = 0;
	while (proc->process[i][*j])
	{
		if (proc->process[i][*j] == 32)
		{
			if (proc->added_spc_arr_len < proc->added_spc_arr_length[i][0]
			&& proc->added_spc_arr[i][proc->added_spc_arr_len] == *j)
			{
				proc->added_spc_arr_len++;
				lock = 1;
			}
			else if (proc->exp_sp_arr[*sp_len] == 2)
			{
				*sp_len += 1;
				lock = 1;
			}
			else
				*sp_len += 1;
			if (lock == 1)
			{
				*j += 1;
				break ;
			}
		}
		col++;
		*j += 1;
	}
	return (col);
}

char	**ft_split_sp(t_proc *proc, int i, int *sp_len, int *k)
{
	char	**args;
	int		row;
	int		j;
	int		col;
	int		tmp;

	tmp = *sp_len;
	proc->row_len = ft_count_row(proc, sp_len, i);
	*sp_len = tmp;
	args = (char **)malloc(sizeof(char *) * (proc->row_len + 1));
	row = 0;
	j = 0;
	*k = 0;
	proc->added_spc_arr_len = 0;
	while (row < proc->row_len)
	{
		col = 0;
		proc->col_len = ft_count_col(proc, i, &j, sp_len);
		args[row] = malloc(sizeof(char) * proc->col_len + 1);
		while (col < proc->col_len)
			args[row][col++] = proc->process[i][(*k)++];
		*k += 1;
		args[row++][col] = '\0';
	}
	args[row] = NULL;
	return (args);
}

void	ft_tokenizer(t_proc *proc)
{
	int		i;
	char	**args;
	int		sp_len;
	int		k;

	i = 0;
	k = 0;
	sp_len = 0;
	ft_exp_sp_arr(proc);
	proc->lst = malloc(sizeof(t_node) * proc->process_count);
	ft_memset((proc->lst), 0, sizeof(t_node *));
	ft_redirection_parse(proc);
	proc->added_spc_arr_len = 0;
	while (i < proc->process_count)
	{
		proc->added_spc_arr_len = 0;
		args = ft_split_sp(proc, i, &sp_len, &k);
		ft_add_node_back(proc, proc->lst, ft_new_node(args));
		ft_free_double_char(args);
		i++;
	}
	print_args(proc);
}
