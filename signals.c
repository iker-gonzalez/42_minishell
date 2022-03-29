/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:26:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/29 12:02:02 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

t_sig	g_sig;

void	child_message(int signum)
{
	if (signum == SIGQUIT)
	{
		g_sig.status = 131;
		printf("Quit 3\n");
	}
	else if (signum == SIGINT)
	{
		g_sig.status = 130;
		printf("\n");
	}
}

void	handler(int signum)
{
	if (!g_sig.act_child)
	{
		if (signum == SIGINT)
		{
			g_sig.status = 1;
			printf("\n");
			rl_on_new_line();
			//rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		g_sig.status = 127;
		printf("%c", '\r');
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (g_sig.pid == 0)
	{
		g_sig.act_child = 0;
		exit(0);
	}
	child_message(signum);
}

void	listen_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
