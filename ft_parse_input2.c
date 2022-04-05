/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:10:57 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/05 16:49:51 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// These two functions are used to determine the preference of quotes.
// If proc->quote_scope = 4, preference for double quotes.
// If proc->quote_scope = 2, preference for single quotes.
// If proc->quote_scope != 4 && !=2, preference is not applicable.

int	ft_quote_pref_close(char *line_read, int i)
{
	int	ret;

	while (line_read[i])
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
	int	scope;

	i = 0;
	scope = 0;
	while (proc->line_read[i] && proc->line_read[i] != 34
		&& proc->line_read[i] != 39)
		i++;
	if (proc->line_read[i] == 39)
		proc->quote_scope = 1 + (ft_quote_pref_close(proc->line_read, i));
	else if (proc->line_read[i] == 34)
		proc->quote_scope = 2 + (ft_quote_pref_close(proc->line_read, i));
}

int	ft_expand_dollar(t_proc *proc, int *i)
{
	if (!proc->single_quote || (proc->quote_scope == 4 && (proc->double_quote)))
	{
		if (proc->line_read[*i] == '$' && proc->line_read[*i + 1] == '?')
		{
			ft_expand_exit(proc);
			*i += 2;
			return (1);
		}
		else if (proc->line_read[*i] == '$')
		{
			*i += 1;
			ft_expand_env(proc, i);
			return (1);
		}
	}
	return (0);
}
