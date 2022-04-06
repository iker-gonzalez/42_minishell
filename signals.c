/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 17:26:53 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/06 17:27:48 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	child_message(int signum)
{
	if (signum == SIGQUIT)
	{
		g_sig.exit_status = 131;
		printf("Quit 3\n");
		g_sig.act_child = 0;
	}
	else if (signum == SIGINT)
	{
		g_sig.exit_status = 130;
		printf("\n");
		g_sig.act_child = 0;
	}
}

void	handler(int signum)
{
	if (!g_sig.act_child)
	{
		if (signum == SIGINT)
		{
			g_sig.exit_status = 1;
			printf("\n");
			rl_on_new_line();
	//		rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		return ;
	}
	child_message(signum);
}

void	listen_signals(void)
{
	//rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
