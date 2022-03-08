/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:03:22 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/05 14:03:10 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_quote (t_proc *proc, char c, int *i)
{
	if (c == 39 && (!proc->single_quote) && proc->double_quote)
		proc->single_quote = 2;
	else if (c == 39 && (!proc->single_quote))
		proc->single_quote = 1;
	else if (c == 39 && proc->single_quote)
		proc->single_quote = 0;
	else if (c == 34 && (!proc->double_quote) && proc->single_quote)
		proc->single_quote = 2;
	else if (c == 34 && (!proc->double_quote))
		proc->double_quote = 1;
	else if (c == 34 && proc->double_quote)
		proc->double_quote = 0;
	*i += 1;
}

void	ft_trm_quotes(t_proc *proc)
{
	int i;

	i = 0;
	(*proc->lst)->exp_content = malloc(sizeof(char) * ft_strlen((*proc->lst)->content) + 1);
	while ((*proc->lst)->content[i])
	{
		if (((*proc->lst)->content[i] == 39 && (!(proc->double_quote))))
			ft_set_quote(proc, (*proc->lst)->content[i], &i);
		else if (((*proc->lst)->content[i] == 34 && (!(proc->single_quote))))
			ft_set_quote(proc, (*proc->lst)->content[i], &i);
		else if (((*proc->lst)->content[i] == 36 && proc->single_quote != 1 && ++i))
			ft_trm_dollar((*proc->lst), &i);
		else
			(*proc->lst)->exp_content[(*proc->lst)->exp_len++] = (*proc->lst)->content[i++];
	}
	(*proc->lst)->exp_content[(*proc->lst)->exp_len] = '\0';
}

void	ft_transform_input(t_proc *proc)
{
	ft_lstiter(proc, ft_trm_quotes);
    print_list(proc, proc->lst);
}