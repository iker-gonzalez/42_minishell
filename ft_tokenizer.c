/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/09 09:56:36 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_row(t_proc *proc, char *process, int *sp_len)
{
	int	count_y;
	int	i;

	i = -1;
	count_y = 1;
	while (process[++i])
	{
		if (process[i] == 32)
		{
			if (*sp_len < proc->exp_space_count
				&& proc->exp_sp_arr[*sp_len] == 2)
				count_y++;
			*sp_len += 1;
		}
	}
	return (count_y);
}

int	ft_count_col(t_proc *proc, char *process, int *i, int *sp_len)
{
	int	col;
	int	lock;

	col = 0;
	lock = 0;
	while (process[*i])
	{
		if (process[*i] == 32)
		{
			if (proc->exp_sp_arr[*sp_len] == 2)
				lock = 1;
			*sp_len += 1;
			if (lock == 1)
			{
				*i += 1;
				break ;
			}
		}
		col++;
		*i += 1;
	}
	return (col);
}

char	**ft_split_sp(t_proc *proc, char *process, int *sp_len, int *k)
{
	char	**args;
	int		row;
	int		i;
	int		col;
	int		tmp;

	tmp = *sp_len;
	proc->row_len = ft_count_row(proc, process, sp_len);
	*sp_len = tmp;
	args = (char **)malloc(sizeof(char *) * (proc->row_len + 1));
	row = 0;
	i = 0;
	*k = 0;
	while (row < proc->row_len)
	{
		col = 0;
		proc->col_len = ft_count_col(proc, process, &i, sp_len);
		args[row] = malloc(sizeof(char) * proc->col_len + 1);
		while (col < proc->col_len)
			args[row][col++] = process[(*k)++];
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
	while (i < proc->process_count)
	{
		args = ft_split_sp(proc, proc->process[i], &sp_len, &k);
		ft_add_node_back(proc, proc->lst, ft_new_node(args));
		ft_free_double_char(args);
		i++;
	}
	//proc->head = (*proc->lst);
	//(*proc->lst) = proc->head;

	print_args(proc);
}
