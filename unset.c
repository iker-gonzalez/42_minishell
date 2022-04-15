/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 08:33:03 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 20:39:47 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_errors(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_isalpha(argv[0]) && argv[0] != '_')
		{
			ft_putendl_fd("papa$hell: unset: not a valid identifier", 2);
			return (1);
		}
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			ft_putendl_fd("papa$hell: unset: not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**rmv_var(t_set *set, char *var)
{
	int		i;
	char	**tmp;
	int		k;

	i = -1;
	k = 0;
	while (set->env[++i])
	{
		if (ft_strncmp(set->env[i], var, ft_strlen(var)) == 0)
			k++;
	}
	tmp = (char **)malloc(sizeof(char *) * (i - k + 1));
	i = -1;
	k = 0;
	while (set->env[++i])
	{
		if (ft_strncmp(set->env[i], var, ft_strlen(var)) != 0)
			tmp[k++] = ft_strdup(set->env[i]);
	}
	tmp[k] = NULL;
	ft_free_double_char(set->env);
	return (tmp);
}

int	unset(t_set *set, char **argv, int child)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			ft_putendl_fd("papa$hell: unset: not a valid identifier", 2);
		else if (!ft_unset_errors(argv[i]))
			set->env = rmv_var(set, argv[i]);
		i++;
	}
	if (child)
		exit (0);
	return (0);
}
