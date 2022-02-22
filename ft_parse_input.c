#include "minishell.h"

int    ft_findchar(t_node *node, char c)
{
    int i;

    i = 0;
    while(node->content[i])
    {
        if ((node->content[i]) == c)
            return (1);
        i++;
    }
    return (0);
}


void    ft_parse_quotes(t_proc *proc, char c)
{
    int lock;
    t_node *head;

    head = (*proc->lst);
    lock = 0;
    while (*proc->lst)
    {
        if (ft_findchar(*proc->lst, c))
        {
            (*proc->lst)->double_quoted = 1;
            if (lock == 0)
                (*proc->lst) = (*proc->lst)->next;
            lock = 1;
            while (!ft_findchar((*proc->lst), c))
            {
                (*proc->lst)->double_quoted = 1;
                (*proc->lst) = (*proc->lst)->next;
            }
            (*proc->lst)->double_quoted = 1;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = head;
}


void    ft_parse_input(t_proc *proc)
{
    ft_gen_lst(proc);
    ft_parse_quotes(proc, 34);
    ft_parse_quotes(proc, 39);
    print_list(proc->lst);
}
