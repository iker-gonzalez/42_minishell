/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:10:57 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/11 10:50:22 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_expand_dollar(t_proc *proc, int *i)
{
	if (!proc->single_quote)
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
