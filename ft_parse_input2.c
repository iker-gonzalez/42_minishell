/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:10:57 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/11 18:19:56 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_pref_close(char *line_read, int i)
{
	int ret;

	while(line_read[i])
	{
		if (line_read[i] == 39)
			ret = 1;
		else if (line_read[i] == 34)
			ret = 2;
		i++;
	}
	return (ret);
}

void	ft_quote_pref_open(t_proc *proc)
{
	int	i;
	int scope;

	i = 0;
	scope = 0;
	while (proc->line_read[i] && proc->line_read[i] != 34 && proc->line_read[i] != 39)
		i++;
	if (proc->line_read[i] == 39)
		proc->quote_scope = 1 + (ft_quote_pref_close(proc->line_read, i));
	else if (proc->line_read[i] == 34)
		proc->quote_scope = 2 + (ft_quote_pref_close(proc->line_read, i));
}

int    ft_findchar(char *line, char c)
{
    int i;
    int k;

    i = 0;
    k = 0;
    if (line[i])
    {
        while(line[i])
        {
            if ((line[i]) == c)
                k++;
            i++;
        }
    }
    return (k);
}