/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c											:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:56:51 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 11:56:52 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_fork;

/*
 * Перехватывает SIGINT
 * Посылает дочерним процессам SIGKILL
 */

static void	signal_handler(int sig)
{
	(void) sig;
	if (g_fork >= 0)
		kill(g_fork, SIGKILL);
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
 * Перехватывает SIGSEGV
 */

static void	sig_seg(int code)
{
	(void) code;
	ft_putstr_fd("Ошибка сегментации.\n", 1);
}

/*
 * Перехватывает SIGABRT
 */

static void	sig_sbrt(int code)
{
	(void) code;
	ft_putstr_fd("Аборт.\n", 1);
}

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, &sig_seg);
	signal(SIGABRT, &sig_sbrt);
}
