/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_args_red.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:39:34 by jsolinis          #+#    #+#             */
/*   Updated: 2022/04/08 22:50:13 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_red_proc(char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == 62 || arg[j] == 60)
			return (j);
		j++;
	}
	return (-1);
}

int	ft_contain_red(char *arg)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	while (arg[j])
	{
		if (arg[j] == 62 || arg[j] == 60)
			ret = 1;
		j++;
	}
	return (ret);
}

char	*ft_set_alltogether(char *arg, int i)
{
	int		j;
	char	*ret;

	ret = malloc(i + 1);
	j = 0;
	while (i > j)
	{
		ret[j] = arg[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);	
}

void	ft_set_args_red(t_proc *proc)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	(*proc->lst)->reds = 0;
	while ((*proc->lst)->args[i])
		i++;
	(*proc->lst)->args_red = malloc (sizeof(char *) * (i + 1));
	i = 0;
	while ((*proc->lst)->args[i])
	{
		if (!ft_contain_red((*proc->lst)->args[i]))
			(*proc->lst)->args_red[k++] = (*proc->lst)->args[i];
		else
		{
			(*proc->lst)->reds = k;
			if (ft_strlen((*proc->lst)->args[i]) == 1)
				i++;
			else if (ft_find_red_proc((*proc->lst)->args[i]) == (ft_strlen((*proc->lst)->args[i]) - 1))
			{
				(*proc->lst)->args_red[k++] = ft_set_alltogether((*proc->lst)->args[i], ft_find_red_proc((*proc->lst)->args[i]));
				
				ft_set_route(proc, (*proc->lst)->args_red[0]);
				i++;
			}
			else if (ft_find_red_proc((*proc->lst)->args[i]) != 0)
			{
				(*proc->lst)->args_red[k++] = ft_set_alltogether((*proc->lst)->args[i], ft_find_red_proc((*proc->lst)->args[i]));
				ft_set_route(proc, (*proc->lst)->args_red[0]);
			}
			else
				ft_set_route(proc, (*proc->lst)->args[0]);
		}
		i++;
	}
	if ((*proc->lst)->reds == 0)
		(*proc->lst)->args_red[k] = NULL;
	else
		(*proc->lst)->args_red[(*proc->lst)->reds] = NULL;
}
