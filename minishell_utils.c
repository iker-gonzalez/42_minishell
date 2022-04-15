/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:34:04 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 13:28:16 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_findchar(char *line, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (line[i])
	{
		while (line[i])
		{
			if ((line[i]) == c)
				k++;
			i++;
		}
	}
	return (k);
}

int	ft_find_red(t_proc *proc, char *process, int *i)
{
	if (process[*i] == 60 && process[*i + 1] == 60)
	{
		if (proc->red_in_app_arr[proc->red_in_app_arr_len++] == 1)
		{
			*i += 1;
			return (1);
		}
	}
	return (0);
}

void	ft_exp_sp_arr(t_proc *proc)
{
	int	i;
	int	k;

	i = -1;
	proc->exp_sp_arr_len = 0;
	while (++i < proc->space_count)
	{
		if (proc->space_arr[i] != 1)
			proc->exp_sp_arr_len++;
	}
	if (!proc->exp_sp_arr_len)
		return ;
	proc->exp_sp_arr = malloc(sizeof(int) * proc->exp_sp_arr_len);
	i = -1;
	k = 0;
	while (++i < proc->space_count)
	{
		if (proc->space_arr[i] != 1)
			proc->exp_sp_arr[k++] = proc->space_arr[i];
	}
	proc->exp_space_count = k;
}

int	ft_strncmp_len(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while (i < n)
	{
		if (str1[i] < str2[i])
			return (-1);
		else if (str1[i] > str2[i])
			return (1);
		if (str1[i] == '\0' || str2 == NULL)
			break ;
		i++;
	}
	return (0);
}

int	ft_count_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
