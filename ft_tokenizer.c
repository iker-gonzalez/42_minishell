/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/18 10:59:46 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_check_redirections(t_proc *proc, char *process, int *i)
{
	if (process[*i] == 60)
	{
		if (process[*i+1] == 60)
		{
			if(proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
			{
				proc->token_count++;
			}
			*i += 2;
		}
		else if (proc->red_in_arr[proc->red_in_arr_len++] == 1)
		{
			proc->token_count++;
			if (process[*i+1] == 32)
				proc->token_count++;
			*i += 1;
		}
	}
	else if (process[*i] == 62)
	{
		if (process[*i+1] == 62)
		{
			if(proc->red_out_del_arr[proc->red_out_del_arr_len++] == 1)
			{
				proc->token_count++;
			}
			*i += 2;
		}
		else if (proc->red_out_arr[proc->red_out_arr_len++] == 1)
		{
			proc->token_count++;
			if (process[*i+1] == 32)
				proc->token_count++;
			*i += 1;
		}
	}
}

void	ft_count_tokens(t_proc *proc, char *process)
{
	int i;
	int k;
	
	i = 0;
	if (ft_strlen(proc->line_read) > 0)
		proc->token_count = 1;
	proc->red_in_arr_len = 0;
	proc->red_in_app_arr_len = 0;
	proc->red_out_arr_len = 0;
	proc->red_out_del_arr_len = 0;
	while (process[i])
	{
		k = proc->token_count;
		if (process[i] == 32 && proc->space_arr[proc->space_arr_len++] != 3 && process[i+1] != 32)
		{
			proc->token_count++;
		}
		else if ((process[i] == 60 || process[i] == 62) && (process[i-1] != 32 || process[i+1] != 32))
		{
			ft_check_redirections(proc, process, &i);
			if (k != proc->token_count && process[i+1] != 32 && process[i-1] != 32)
					proc->token_count++;
		}
		i++;
	}
	printf("Token count: %d\n", proc->token_count);
}
*/
/*
void	ft_arrange_input(t_proc *proc)
{
	int i;

	i = 0;
	proc->space_arr_len = 0;
	while (i < proc->process_count)
	{
		ft_count_tokens(proc, proc->process[i]);
		ft_gen_lst(proc);
		if (i < proc->process_count)
			proc->space_arr_len += 2;
		i++;
	}
}
*/

void	ft_exp_sp_arr(t_proc *proc)
{
	int i;
	int k;

	i = -1;
	proc->exp_sp_arr_len = 0;
	while (++i < proc->space_count)
	{
		if (proc->space_arr[i] != 1)
			proc->exp_sp_arr_len++;
	}
	proc->exp_sp_arr = malloc(sizeof(int) * proc->exp_sp_arr_len);
	i = -1;
	k = 0;
	while (++i < proc->space_count)
	{
		if (proc->space_arr[i] != 1)
			proc->exp_sp_arr[k++] = proc->space_arr[i];
	}
	proc->exp_space_count = k;
}

int	ft_count_row(t_proc *proc, char *process, int *sp_len)
{
	int	count_y;
	int i;
	
	i = -1;
	if (ft_strlen(process) > 0)
		count_y = 1;
	while (process[++i])
	{
		if (process[i] == 32)
		{
			if (*sp_len < proc->exp_space_count && proc->exp_sp_arr[*sp_len] == 2)
				count_y++;
			*sp_len += 1;
		}
	}
	return(count_y);
}

int	ft_count_col(t_proc *proc, char *process, int *i, int *sp_len)
{
	int col;
	int lock;

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
	char **args;
	int row;
	int i;
	int row_len;
	int col_len;
	int col;
	int tmp;

	tmp = *sp_len;
	row_len = ft_count_row(proc, process, sp_len);
	*sp_len = tmp;
	args = (char **)malloc(sizeof(char *) * (row_len + 1));
	row = 0;
	col_len = 0;
	i = 0;
	*k = 0;
	while (row < row_len)
	{
		col = 0;
		col_len = ft_count_col(proc, process, &i, sp_len);
		args[row] =  malloc(sizeof(char) * col_len + 1);
		while (col < col_len)
		{
			args[row][col] = process[*k];
			*k +=1;
			col++;
		}
		*k +=1;
		args[row][col] = '\0';
		row++;
	}
	args[row] = NULL;
	return(args);
}


void	ft_make_it(t_proc *proc)
{
	int i;
	char **args;
	int sp_len;
	int k;

	i = 0;
	k = 0;
	sp_len = 0;
	//proc->exp_sp_arr_len = 0;
	proc->lst = malloc(sizeof(t_node) * proc->process_count);
	ft_memset((proc->lst), 0, sizeof(t_node *));
	while (i < proc->process_count)
	{
		args = ft_split_sp(proc, proc->process[i], &sp_len, &k);
		//proc->exp_sp_arr_len = 0;
		ft_add_node_back(proc->lst, ft_new_node(args));
		//ft_gen_lst(proc, args, row_len);
		i++;
	}
	ft_lstiter(proc, print_list);
}


void	ft_tokenizer33(t_proc *proc)
{
	ft_exp_sp_arr(proc);
	ft_make_it(proc);
}
