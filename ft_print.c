#include "minishell.h"

void    ft_print_val(t_proc *proc)
{
//	int pipe_count;
	int i;
	int row;
	int col;

    printf("LINE_EXP: %s\n", proc->line_expanded);
/*    printf("EXP_LEN: %d\n", proc->line_exp_len);
	pipe_count = ft_findchar(proc->line_read, 124);
	i = 0;
	printf("EXP PIPES: ");
	while (i < pipe_count)
	{
		printf("%d", proc->pipe_arr[i]);
		i++;
	}
	printf("\n");
	i = 0;
	printf("EXP RED_IN: ");
	while (i < proc->red_in_count)
	{
		printf("%d", proc->red_in_arr[i]);
		i++;
	}
	printf("\n");
	printf("EXP RED_IN_APP: ");
	i = 0;
	while (i < proc->red_in_app_count)
	{
		printf("%d", proc->red_in_app_arr[i]);
		i++;
	}
	printf("\n");
	printf("EXP RED_OUT: ");
	i = 0;
	while (i < proc->red_out_count)
	{
		printf("%d", proc->red_out_arr[i]);
		i++;
	}
	printf("\n");
	printf("EXP RED_OUT_DEL: ");
	i = 0;
	while (i < proc->red_out_del_count)
	{
		printf("%d", proc->red_out_del_arr[i]);
		i++;
	}
	printf("\n");*/
	printf("EXP SPACES: ");
	i = 0;
	while (i < proc->space_count)
	{
		printf("%d", proc->space_arr[i]);
		i++;
	}
	printf("\n");
	printf("EXP EXP SPACES: ");
	i = 0;
	while (i < proc->exp_sp_arr_len)
	{
		printf("%d", proc->exp_sp_arr[i]);
		i++;
	}
	printf("\n");
	printf("TOKENS: \n");
	row = 0;
	while (row < proc->process_count)
	{
		printf("Process %d\n", row);
		printf("=============\n");
		col = 0;
		while (proc->process[row][col])
		{
			printf("%c", proc->process[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

void print_args (t_proc *proc)
{
		int i;
		int k;

	while ((*proc->lst))
	{
		i = 0;
		while ((*proc->lst)->args[i])
		{
			k = 0;
			printf ("token %d:\n", i);
			while ((*proc->lst)->args[i][k])
			{
				printf("%c", (*proc->lst)->args[i][k]);
				k++;
			}
			i++;
			printf("\n");
		}
		printf("==============================\n");
		(*proc->lst) = (*proc->lst)->next;
	}
}
