/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:17:46 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/14 21:20:42 by jsolinis         ###   ########.fr       */
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

void	ft_set_env(t_set *set, char *arg)
{
	int	k;
	int	edit;

	k = -1;
	if (!ft_export_errors(arg))
		edit = 0;
	while (set->env[++k])
	{
		if (((ft_strncmp(set->env[k], arg, ft_varlen(arg))) == 0)
			&& ++edit)
			set->env = edit_var(set, arg);
	}
	if (!edit)
		set->env = add_var(set, arg);
}

int	export(t_set *set, char **argv, int child, int fd)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = ft_count_argc(argv);
	if (cmd_count == 1)
		print_sorted_env(set, fd);
	else if (argv[1][0] == 62)
		print_sorted_env(set, fd);
	while (argv[++i])
		ft_set_env(set, argv[i]);
	if (child)
		exit (0);
	return (0);
}
