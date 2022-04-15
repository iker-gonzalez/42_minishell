/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:45:08 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 20:54:20 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_errors(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[0]) && argv[0] != '_')
	{
		ft_putendl_fd("papa$hell: export: not a valid identifier", 2);
		return (1);
	}
	if (!ft_findchar(argv, '='))
		return (1);
	while (argv[i] != '=')
	{
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
		{
			ft_putendl_fd("papa$hell: export: not a valid identifier", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_varlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char	**edit_var(t_set *set, char *var)
{
	int	var_len;
	int	i;

	var_len = ft_varlen(var);
	i = -1;
	while (set->env[++i])
	{
		if ((ft_strncmp(set->env[i], var, var_len) == 0))
		{
			free(set->env[i]);
			set->env[i] = ft_strdup(var);
		}
	}
	return (set->env);
}

char	**add_var(t_set *set, char *var)
{
	int		i;
	char	**tmp;

	i = 0;
	while (set->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (set->env[++i])
			tmp[i] = ft_strdup(set->env[i]);
	tmp[i] = ft_strdup(var);
	tmp[i + 1] = NULL;
	ft_free_double_char(set->env);
	return (tmp);
}

int	export(t_proc *proc, char **argv, int child, int fd)
{
	int	i;
	int	k;

	i = 0;
	if ((ft_count_argc(argv)) == 1)
		print_sorted_env(proc, proc->set, fd);
	while (argv[++i])
	{
		k = -1;
		if (!ft_export_errors(argv[i]))
		{
			proc->ex = 0;
			while (proc->set->env[++k])
			{
				if (((ft_strncmp(proc->set->env[k], argv[i],
								ft_varlen(argv[i]))) == 0) && ++proc->ex)
					proc->set->env = edit_var(proc->set, argv[i]);
			}
			if (!proc->ex)
				proc->set->env = add_var(proc->set, argv[i]);
		}
	}
	if (child)
		exit (0);
	return (0);
}
