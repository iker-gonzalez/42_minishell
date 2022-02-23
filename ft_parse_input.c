#include "minishell.h"

int    ft_findchar(t_node *node, char c)
{
    int i;
    int k;

    i = 0;
    k = 0;
    if (node)
    {
        while(node->content[i])
        {
            if ((node->content[i]) == c)
                k++;
            i++;
        }
    }
    return (k);
}

void    ft_parse_dollar(t_proc *proc)
{
    while (*proc->lst)
    {
        if ((*proc->lst)->content[0] == '$')
            (*proc->lst)->dollar = 1;
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}

void    ft_parse_dquotes(t_proc *proc, char c)
{
    int lock;

    lock = 0;
    while (*proc->lst)
    {
        if (ft_findchar(*proc->lst, c))
        {
            (*proc->lst)->double_quoted = 1;
            if (lock == 0 && (*proc->lst)->next && (ft_findchar((*proc->lst), c) %2) != 0)
                (*proc->lst) = (*proc->lst)->next;
            lock = 1;
            while (!ft_findchar((*proc->lst), c) && (*proc->lst)->next)
            {
                (*proc->lst)->double_quoted = 1;
                (*proc->lst) = (*proc->lst)->next;
            }
            lock = 0;
            if (ft_findchar((*proc->lst), c))
                (*proc->lst)->double_quoted = 1;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}

void    ft_parse_squotes(t_proc *proc, char c)
{
    int lock;

    lock = 0;
    while (*proc->lst)
    {
        if (ft_findchar(*proc->lst, c))
        {
            (*proc->lst)->single_quoted = 1;
            if (lock == 0 && (*proc->lst)->next && (ft_findchar((*proc->lst), c) %2) != 0)
                (*proc->lst) = (*proc->lst)->next;
            lock = 1;
            while (!ft_findchar((*proc->lst), c) && (*proc->lst)->next)
            {
                (*proc->lst)->single_quoted = 1;
                (*proc->lst) = (*proc->lst)->next;
            }
            lock = 0;
            if (ft_findchar((*proc->lst), c))
                (*proc->lst)->single_quoted = 1;
        }
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = proc->head;
}


void    ft_parse_input(t_proc *proc)
{
    ft_gen_lst(proc);
    ft_parse_dquotes(proc, 34);
    ft_parse_squotes(proc, 39);
    ft_parse_dollar(proc);
    print_list(proc->lst);
}
