/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:37:59 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/10 07:51:46 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	ft_rmv_dollar(t_(*proc->lst) *(*proc->lst))
{
	int	i;
	int	k;

	if ((ft_count_char((*proc->lst), 36)) == 1)
	{
		(*proc->lst)->exp_content = malloc(sizeof(char) * ft_strlen((*proc->lst)->content));
		i = 0;
		k = 0;
		while ((*proc->lst)->content[i++] != 36)
			(*proc->lst)->exp_content[i] = (*proc->lst)->content[i];
		if(!(*proc->lst)->single_quoted)
		{
			i++;
			(*proc->lst)->exp_content[i] = (*proc->lst)->content[i];
		}
	}
}
*/

int	ft_determine(char *line_read, int i)
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

void	ft_determine_scope(t_proc *proc)
{
	int	i;
	int scope;

	i = 0;
	scope = 0;
	while (proc->line_read[i] && proc->line_read[i] != 34 && proc->line_read[i] != 39)
		i++;
	if (proc->line_read[i] == 39)
		proc->quote_scope = 1 + (ft_determine(proc->line_read, i));
	else if (proc->line_read[i] == 34)
		proc->quote_scope = 2 + (ft_determine(proc->line_read, i));
	printf("quote_scope: %d\n", proc->quote_scope);
}
