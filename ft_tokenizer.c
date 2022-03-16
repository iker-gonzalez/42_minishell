/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 18:07:29 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/16 16:38:36 by ikgonzal         ###   ########.fr       */
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

int	ft_count_row(t_proc *proc, char *process)
{
	int	count_y;
	int i;
	
	i = -1;
	if (ft_strlen(process) > 0)
		count_y = 1;
	while (process[++i])
	{
		if (process[i] == 32 && proc->exp_sp_arr[proc->exp_sp_arr_len++] == 2)
			count_y++;
		
	}
	printf("count_y: %d\n", count_y);
	return(count_y);
}

int	ft_count_col(t_proc *proc, char *process, int *i)
{
	int col;

	col = 0;
	while (process[*i] && proc->exp_sp_arr_len <= proc->exp_space_count)
	{
		if (process[*i] == 32 && proc->exp_sp_arr[proc->exp_sp_arr_len++] == 2)
		{
			*i += 1;
			break ;
		}
		col++;
		*i += 1;
	}
	return (col);
}


char	**ft_split_sp(t_proc *proc, char *process)
{
	char **args;
	int row;
	//int col;
	int i;
	int row_len;
	int col_len;
	int col;
	static int k;

	row_len = ft_count_row(proc, process);
	args = (char **)malloc(sizeof(char *) * (row_len + 1));
	row = 0;
	col_len = 0;
	proc->exp_sp_arr_len = 0;
	i = 0;
	printf("row_len: %d\n", row_len);
	k = 0;
	while (row < row_len)
	{
		col = 0;
		col_len = ft_count_col(proc, process, &i);
		args[row] =  malloc(sizeof(char) * col_len + 1);
		printf("token %d:\n", row);
		while (col < col_len)
		{
			args[row][col] = process[k];
			printf("%c", args[row][col]);
			k++;
			col++;
		}
		k++;
		printf("\n");
		args[row][col] = '\0';
		row++;
	}
	printf("\n");
	return(args);
}
/*
void	ft_print_args(char **args)
{
	int row;
	int col;

	row = 0;
	while (args[row])
	{
		col = 0;
		while(args[row][col])
		{
			printf("%c", args[row][col]);
			col++;
		}
		printf(" ");
		row++;
	}
	printf("\n");
}
*/


void	ft_make_it(t_proc *proc)
{
	int i;
	char **args;

	i = 0;
	proc->exp_sp_arr_len = 0;
	while (i < proc->process_count)
	{
		args = ft_split_sp(proc, proc->process[i]);
		//ft_print_args(args);
		/*ft_gen_lst(proc);
		if (i < proc->process_count)
			proc->space_arr_len += 2;*/
		i++;
	}
}


void	ft_tokenizer33(t_proc *proc)
{
	ft_exp_sp_arr(proc);
	ft_make_it(proc);
}
