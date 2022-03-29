/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 08:33:03 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 11:59:09 by ikgonzal         ###   ########.fr       */
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

char	**rmv_var(t_proc *proc, char *var)
{
	int		i;
	char	**tmp;
	int		k;

	i = -1;
	k = 0;
	while (proc->env[++i])
	{
		if (ft_strncmp(proc->env[i], var, ft_strlen(var)) == 0)
			k++;
	}
	tmp = (char **)malloc(sizeof(char *) * (i - k + 1));
	i = -1;
	k = 0;
	while (proc->env[++i])
	{
		if (ft_strncmp(proc->env[i], var, ft_strlen(var)) != 0)
			tmp[k++] = ft_strdup(proc->env[i]);
	}
	tmp[k] = NULL;
	ft_free_double_char(proc->env);
	return (tmp);
}

void	unset(t_proc *proc, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_unset_errors(argv[i]))
			proc->env = rmv_var(proc, argv[i]);
		i++;
	}
}
