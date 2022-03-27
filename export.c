/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:17:46 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/27 20:18:15 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* export unset cd exit =>si solo hay un proceso, lo ejecutará
 *  en todo caso el padre. Si no el hijo, si bien los cambios no
 *  se verán reflejados (moriran con el hijo). p.e.=> ls | export a=2 
 *  en este caso el export lo haría el hijo, si bien no podriamos ver 
 *  la variable en env ya que este cambio muere cuando el hijo deja
 *  de ejecutarse.*/

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

char	**add_edit_var(t_proc *proc, char *var)
{
	int		i;
	char	**tmp;
	int		edit;

	i = 0;
	edit = 0;
	while (proc->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (proc->env[++i])
	{
		if (ft_strncmp(proc->env[i], var, ft_varlen(var)) == 0 && ++edit)
			tmp[i] = ft_strdup(var);
		else
			tmp[i] = ft_strdup(proc->env[i]);
	}
	if (!edit)
	{
		tmp[i] = ft_strdup(var);
		tmp[i + 1] = NULL;
	}
	else
		tmp[i] = NULL;
	ft_free_double_char(proc->env);
	return (tmp);
}

void	export(t_proc *proc, char **argv)
{
	int	i;

	//$ in first position: as long as we expand first, error is not detected.
	i = 1;
	while (argv[i])
	{
		if (!ft_export_errors(argv[i]))
			proc->env = add_edit_var(proc, argv[i]);
		i++;
	}
}
