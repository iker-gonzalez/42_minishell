#include "minishell.h"

void ft_gen_lst(t_proc *proc)
{
    int i;

    proc->lst = malloc(sizeof(t_node) * proc->cmd_count);
    ft_memset((proc->lst), 0, sizeof(t_node *));
    i = 0;
    while (proc->tokens[i])
    {
        ft_add_node_back(proc->lst, ft_new_node(proc->tokens[i]));
        i++;
    }
}

void    ft_parse_input(t_proc *proc)
{
    int i;

    proc->tokens = ft_split(proc->line_read, ' ');
    i = 0;
    while (proc->tokens[i])
        i++;
    proc->cmd_count = i;
    ft_gen_lst(proc);
    print_list(proc->lst);
}
