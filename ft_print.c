#include "minishell.h"

void    ft_print_val(t_proc *proc)
{
    printf("LINE_EXP: %s\n", proc->line_expanded);
    printf("EXP_LEN: %d\n", proc->line_exp_len);

}