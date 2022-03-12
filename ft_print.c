#include "minishell.h"

void    ft_print_val(t_proc *proc)
{
	int pipe_count;
	int i;

    printf("LINE_EXP: %s\n", proc->line_expanded);
    printf("EXP_LEN: %d\n", proc->line_exp_len);
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
	printf("\n");
	printf("EXP SPACES: ");
	i = 0;
	while (i < proc->space_count)
	{
		printf("%d", proc->space_arr[i]);
		i++;
	}
	printf("\n");
}
