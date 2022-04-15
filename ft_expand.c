/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:03:22 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 21:07:18 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_env(t_proc *proc, int *i)
{
	char	*str;
	char	*env;
	int		k;
	int		j;

	k = 0;
	str = malloc(sizeof(char) * ft_strlen(proc->line_read) + 1);
	while (proc->line_read && (ft_isalpha(proc->line_read[*i])
			|| proc->line_read[*i] == 95))
	{
		str[k++] = proc->line_read[*i];
		*i += 1;
	}
	str[k] = '\0';
	env = ft_get_env_path(proc->set, str, ft_strlen(str));
	j = 0;
	while (proc->lock && env && env[j])
		proc->line_expanded[proc->line_exp_len++] = env[j++];
	if (env && !proc->lock)
		proc->line_exp_len += ft_strlen(env)
			+ ft_strlen(proc->line_read) - k - 1;
	free (str);
}

void	ft_set_quotes(t_proc *proc, char c)
{
	if (c == 39 && (!proc->single_quote) && (!proc->double_quote))
		proc->single_quote = 1;
	else if (c == 39 && proc->single_quote)
		proc->single_quote = 0;
	else if (c == 34 && (!proc->double_quote) && (!proc->single_quote))
		proc->double_quote = 1;
	else if (c == 34 && proc->double_quote)
		proc->double_quote = 0;
}

void	ft_check_quotes(t_proc *proc, char c, int *i)
{
	if (c == 39 && (!proc->double_quote) && proc->lock)
		proc->line_expanded[proc->line_exp_len++] = 126;
	else if (c == 34 && (!proc->single_quote) && proc->lock)
		proc->line_expanded[proc->line_exp_len++] = 126;
	else
	{
		if (proc->lock)
			proc->line_expanded[proc->line_exp_len++] = proc->line_read[*i];
		else
			proc->line_exp_len++;
	}
	*i += 1;
}

void	ft_expand_line_read(t_proc *proc)
{
	int	i;
	int	ret;

	if (proc->lock)
		proc->line_expanded = malloc(sizeof(char) * proc->line_exp_len + 1);
	i = 0;
	proc->line_exp_len = 0;
	while (i < ft_strlen(proc->line_read) && proc->line_read[i])
	{
		ft_set_quotes(proc, proc->line_read[i]);
		ft_expand_spaces(proc, proc->line_read[i], &i);
		ft_expand_pipe(proc, proc->line_read[i]);
		ft_expand_red_in(proc, proc->line_read[i], &i);
		ft_expand_red_out(proc, proc->line_read[i], &i);
		if ((ft_expand_dollar(proc, &i)) == 1)
			ret = 1;
		else
			ft_check_quotes(proc, proc->line_read[i], &i);
	}
	if (proc->lock && proc->line_expanded)
		proc->line_expanded[proc->line_exp_len] = '\0';
}

void	ft_expand_input(t_proc *proc)
{
	proc->pipe_arr_len = 0;
	proc->red_in_arr_len = 0;
	proc->red_in_app_arr_len = 0;
	proc->red_out_del_arr_len = 0;
	proc->red_out_arr_len = 0;
	proc->space_arr_len = 0;
	proc->lock = 0;
	ft_expand_line_read(proc);
	proc->single_quote = 0;
	proc->double_quote = 0;
	proc->lock = 1;
	ft_expand_line_read(proc);
	proc->line_exp_len = 0;
}
