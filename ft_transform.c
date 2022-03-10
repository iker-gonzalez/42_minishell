/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:03:22 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/10 09:49:16 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	ft_expand_dollar(t_node *node, int *i)
{
	char *str;
	char *env;
	int k;

	k = 0;
	str = malloc(sizeof(char) * ft_strlen(node->content) + 1);
	if (!(ft_isalpha(node->exp_content[*i])))
		node->exp_content[0] = '\0';
	else
		node->exp_content[node->exp_len] = '\0';
	while (ft_isalpha(node->content[*i]))
	{
		str[k++] = node->content[*i];
		*i += 1;
	}
	str[k] = '\0';
	printf("str: %s\n", str);
	env = getenv(str);
	printf("%s\n", env);
	if (env && node->exp_content)
		node->exp_content = ft_strjoin(node->exp_content, env);
	node->exp_len = ft_strlen(node->exp_content);
	free (str);
}

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

void	ft_check_metha(t_proc *proc, char c, int *i)
{
	if (c == 36 && (!proc->single_quote))
	{
		*i += 1;
		ft_expand_dollar((*proc->lst), i);
	}
}


void	ft_trm_quotes(t_proc *proc)
{
	int i;

	(*proc->lst)->exp_content = malloc(sizeof(char) * ft_strlen((*proc->lst)->content) + 1);
	i = 0;
	while ((*proc->lst)->content[i])
	{
		ft_set_switch(proc, (*proc->lst)->content[i]);
		if ((*proc->lst)->content[i] == 36)
			ft_check_metha(proc, (*proc->lst)->content[i], &i);
		else if ((*proc->lst)->content[i] == 39 && (!(proc->double_quote)))
			i++;
		else if ((*proc->lst)->content[i] == 39 && proc->quote_scope == 2)
			i++;
		else if ((*proc->lst)->content[i] == 34 && (!(proc->single_quote)))
			i++;
		else if ((*proc->lst)->content[i] == 34 && proc->quote_scope == 4)
			i++;
		else
			(*proc->lst)->exp_content[(*proc->lst)->exp_len++] = (*proc->lst)->content[i++];
	}
	(*proc->lst)->exp_content[(*proc->lst)->exp_len] = '\0';
}

void	ft_transform_input(t_proc *proc)
{
	ft_determine_scope(proc);
	ft_lstiter(proc, ft_trm_quotes);
	//ft_lstiter(proc, ft_rmv_dollar);
    print_list(proc->lst);
}
