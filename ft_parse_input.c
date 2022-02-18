char ft_iam_double(t_proc *proc, int i)
{
    while(proc->line_read[i])
    {
        if (pro->line_read[i] == 34)
            proc->quoted[i] == 11;
        else if (proc->line_read[i] == 39)
            proc->quoted[i] == 10;
        
    }



}


char    *ft_is_quoted(t_proc *proc)
{
    char    *ret;
    int     i;

    i = 0;
    while (proc->line_read[i])
    {
        while (proc->line_read[i] != 34 || proc->line_read[i] != 39 || NOquoted)
        {
            proc->quoted[i] = 10;
            ret[i] = proc->line_read[i];
            i++;
        }
        if (proc->line_read[i] == 34)
        {
            proc->quoted[i] = 11;
            ft_iam_double(proc, i + 1);
        }
        else if (proc->line_read[i] == 39)
            ft_iam_single(proc, i);

    }
    return (ret);
}

void    ft_parse_input(t_proc *proc)
{
    proc->line_read = ft_is_quoted(proc);
}


/*
proc->cmd_count = 1;
while (proc->line_read[i])
{
    if (proc->line_read[i] == '|')
		proc->cmd_count++;
}
if (proc->cmd_count > 1)
{
    proc->process = ft_split(proc->line_read, '|');
    i = 0;
    while(proc->process[i])
    {
	    ft_tokenizer(proc->process[i], proc, i);
	    i++;
    }
else
    ft_tokenizer(proc->line_read, proc, 0);
*/

    