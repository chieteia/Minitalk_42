/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoshihi <ntoshihi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 02:55:47 by ntoshihi          #+#    #+#             */
/*   Updated: 2021/10/08 10:29:24 by ntoshihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

void	ft_putstr_color(char *msg, char *color)
{
	ft_putstr_fd(color, 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd(RESET, 1);
}

/*
Print message and Exit()
*/
void	terminate(char *message, char *color, int status_code)
{
	ft_putstr_color(message, color);
	exit(status_code);
}

void	set_signal_handler(struct sigaction *sa, \
							void (*handler)(int, siginfo_t*, void*))
{
	ft_bzero(sa, sizeof(struct sigaction));
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	sa->__sigaction_u.__sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == FAILED)
		terminate(ERROR_SIGACTION, RED, 1);
	if (sigaction(SIGUSR2, sa, NULL) == FAILED)
		terminate(ERROR_SIGACTION, RED, 1);
}

void	check_arguments(int argc, char **argv, int mode)
{
	char	*server_pid;

	if (mode == SERVER)
	{
		if (argc != 1)
			terminate(USAGE_SERVER, RED, 1);
	}
	else if (mode == CLIENT)
	{
		if (argc != 3)
			terminate(USAGE_CLIENT, RED, 1);
		server_pid = argv[1];
		if (!*server_pid)
			terminate(INVALID_PID, RED, 1);
		while (*server_pid)
		{
			if (!ft_isdigit(*server_pid++))
				terminate(INVALID_PID, RED, 1);
		}
	}
}
