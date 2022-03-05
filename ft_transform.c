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

void	ft_set_switch (t_proc *proc, char c)
{
	if (c == 39 && (!proc->single_quote))
		proc->single_quote = 1;
	else if (c == 39 && proc->single_quote)
		proc->single_quote = 0;
	else if (c == 34 && (!proc->double_quote))
		proc->double_quote = 1;
	else if (c == 34 && proc->double_quote)
		proc->double_quote = 0;
}

int	ft_quote_switch(t_proc *proc, int i)
{
	while ((*proc->lst)->content[i])
	{
		ft_set_switch(proc, (*proc->lst)->content[i]);
		if ((*proc->lst)->content[i] == 39 && (!(proc->double_quote)))
			i++;
		else if ((*proc->lst)->content[i] == 34 && (!(proc->single_quote)))
			i++;
		else
			(*proc->lst)->exp_content[(*proc->lst)->exp_len++] = (*proc->lst)->content[i++];
	}
	return (i);
}

void    ft_rmv_quotes(t_proc *proc)
{
    int i;
	int k;

	i = 0;
	k = 0;
    (*proc->lst)->exp_content = malloc(sizeof(char) * ft_strlen((*proc->lst)->content) + 1);
	while ((*proc->lst)->content[i])
    {
		if ((*proc->lst)->content[i] == 34 || (*proc->lst)->content[i] == 39)
			i = ft_quote_switch(proc, i);
		else
			(*proc->lst)->exp_content[(*proc->lst)->exp_len++] = (*proc->lst)->content[i++];
    }
	(*proc->lst)->exp_content[(*proc->lst)->exp_len] = '\0';
}

void	ft_lstiter(t_proc *proc, void (*f)(t_proc *))
{
	if (!f)
		return ;
	while ((*proc->lst))
	{
		f((proc));
		(*proc->lst) = (*proc->lst)->next;
	}
	(*proc->lst) = proc->head;
}

void	ft_transform_input(t_proc *proc)
{
	ft_lstiter(proc, ft_rmv_quotes);
	//ft_lstiter(proc, ft_rmv_dollar);
    print_list(proc->lst);
}