/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/16 13:20:50 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_head(t_proc *proc)
{
	int	i;
	int	k;

	proc->head = (*proc->lst);
	while ((*proc->lst))
	{
		i = 0;
		while ((*proc->lst)->args[i])
		{
			k = 0;
			while ((*proc->lst)->args[i][k])
				k++;
			i++;
		}
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}

int	ft_count_row(t_proc *proc, int *sp_len, int i)
{
	int	j;

	j = -1;
	proc->count_y = 1;
	while (proc->process[i][++j])
	{
		if (proc->process[i][j] == 32)
		{
			if (proc->added_spc_arr_len < proc->added_spc_arr_length[i][0]
			&& proc->added_spc_arr[i][proc->added_spc_arr_len] == j)
			{
				proc->added_spc_arr_len++;
				proc->count_y++;
			}
			else if (*sp_len < proc->exp_space_count
				&& proc->exp_sp_arr[*sp_len] == 2)
			{
				proc->count_y++;
				*sp_len += 1;
			}
			else
				*sp_len += 1;
		}
	}
	return (proc->count_y);
}

void	ft_count_col(t_proc *proc, int i, int *j, int *sp_len)
{
	proc->col_len = 0;
	proc->lock_col = 0;
	while (proc->process[i][*j])
	{
		if (proc->process[i][*j] == 32)
		{
			if (proc->added_spc_arr_len < proc->added_spc_arr_length[i][0]
			&& proc->added_spc_arr[i][proc->added_spc_arr_len] == *j)
			{
				proc->added_spc_arr_len++;
				proc->lock_col = 1;
			}
			else if (proc->exp_sp_arr[*sp_len] == 2)
			{
				*sp_len += 1;
				proc->lock_col = 1;
			}
			else
				*sp_len += 1;
			if (proc->lock_col == 1 && (*j)++)
				break ;
		}
		proc->col_len++;
		*j += 1;
	}
}

char	**ft_split_sp(t_proc *proc, int i, int *sp_len, int *k)
{
	char	**args;
	int		j;
	int		col;
	int		tmp;

	tmp = *sp_len;
	proc->row_len = ft_count_row(proc, sp_len, i);
	*sp_len = tmp;
	args = (char **)malloc(sizeof(char *) * (proc->row_len + 1));
	proc->row_tok = 0;
	j = 0;
	*k = 0;
	proc->added_spc_arr_len = 0;
	while (proc->row_tok < proc->row_len)
	{
		col = 0;
		ft_count_col(proc, i, &j, sp_len);
		args[proc->row_tok] = malloc(sizeof(char) * proc->col_len + 1);
		while (col < proc->col_len)
			args[proc->row_tok][col++] = proc->process[i][(*k)++];
		*k += 1;
		args[proc->row_tok++][col] = '\0';
	}
	args[proc->row_tok] = NULL;
	return (args);
}

void	ft_tokenizer(t_proc *proc)
{
	int		i;
	char	**args;
	int		sp_len;
	int		k;
	t_node	*new;

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
		new = ft_new_node(args);
		ft_add_node_back(proc, proc->lst, new);
		ft_free_double_char(args);
		i++;
	}
	ft_set_head(proc);
}
