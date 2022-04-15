/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:26:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 16:43:51 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	child_message(int signum)
{
	if (signum == SIGQUIT)
	{
		g_exit_status = 131;
		printf("Quit 3\n");
	}
	else if (signum == SIGINT)
	{
		g_exit_status = 130;
		printf("\n");
	}
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	return ;
}

void	listen_signals_daddy(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}

void	listen_signals_child(void)
{
	signal(SIGINT, child_message);
	signal(SIGQUIT, child_message);
}
