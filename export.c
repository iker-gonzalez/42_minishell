/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 09:17:46 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/25 12:36:10 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export unset cd exit =>si solo hay un proceso, lo ejecutará en todo caso el padre. 
//Si no el hijo, si bien los cambios no se verán reflejados (moriran con el hijo). p.e.=> ls | export a=2 
//en este caso el export lo haría el hijo, si bien no podriamos ver la variable en env ya que este cambio 
//muere cuando el hijo deja de ejecutarse.

char	**add_edit_var(t_proc *proc, char *var)
{
	int i;
	char **tmp;

	i = 0;
	while (proc->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (proc->env[++i])
	{
		if (!(ft_strncmp(proc->env[i], var, ft_strlen(var))))
			tmp[i] = ft_strdup(proc->env[i]);
		else
			tmp[i] = ft_strdup(proc->env[i]);
	}
	ft_free_double_char(proc->env);
	tmp[i+1] = NULL;
	return (tmp);
}

void	export(t_proc *proc, char **argv)
{
	int i;

	i = 1;
	ft_env(proc);
	printf("\n\n");
	while (argv[i])
	{
		proc->env = add_edit_var(proc, argv[i]);
		i++;
	}
}