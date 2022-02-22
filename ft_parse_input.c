#include "minishell.h"
/*
void    ft_parselist(t_proc *proc, t_node *lst, char c, int *mod)
{
    int i;

    i = 0;
    while (lst->content[i])
    {
        if (lst->content[i] == c)
        {
            if (proc->quote_count == 0)
                *mod = 1;
            else if (proc->quote_count %2 == 0)
                lst->next->double_quoted = 0;
            proc->quote_count++;
        }
        i++;
    }
}
*/

void    ft_parse_input(t_proc *proc)
{
    int i;
   // t_node *head;

    proc->tokens = ft_split(proc->line_read, ' ');
    i = 0;
    while (proc->tokens[i])
        i++;
    proc->cmd_count = i;
    ft_gen_lst(proc);
    /*
    head = (*proc->lst);
    while ((*proc->lst))
    {
        //ft_parselist((*proc->lst), 34, &((*proc->lst)->double_quoted));
        (*proc->lst) = (*proc->lst)->next;
    }
    (*proc->lst) = head;
    print_list(proc->lst);
    */
}
