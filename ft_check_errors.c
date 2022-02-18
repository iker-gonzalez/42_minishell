void    ft_count_quotation_marks(t_prop *proc)
{
    int i;

    i = 0;
    while (proc->line_read[i])
    {
        if (proc->line_read[i] == 34)
            proc->double_quotes++;
        else if (proc->line_read[i] == 39)
            proc->single_quotes++;
    }
    /*
    if (proc->double_quotes %2 != 0 || proc->single_quotes %2 != 0)
    {

    }*/
}