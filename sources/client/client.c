/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoshihi <ntoshihi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 02:55:45 by ntoshihi          #+#    #+#             */
/*   Updated: 2021/10/06 22:03:56 by ntoshihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

static int	g_signal = WAITING_ACK;

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGUSR1)
		g_signal = RECIEVED_ACK;
}

static void	send_packet(pid_t server_pid, char c)
{
	int			bit;
	int			send_signal;
	const int	signals[2] = {SIGUSR2, SIGUSR1};

	bit = CHAR_BIT_SIZE;
	while (bit--)
	{
		send_signal = signals[((c >> bit) & 1)];
		if (kill(server_pid, send_signal) == -1)
			terminate(ERROR_SEND_SIGNAL, RED, 1);
		while (g_signal == WAITING_ACK)
			;
		g_signal = WAITING_ACK;
	}
}

static void	send_message(pid_t server_pid, char *msg)
{
	if (kill(server_pid, 0) == -1)
		terminate(INVALID_PID, RED, 1);
	while (*msg)
		send_packet(server_pid, *msg++);
	send_packet(server_pid, (char)0x4);
	terminate(SUCCESS_MSG_CLIENT, GREEN, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sc;

	check_arguments(argc, argv, CLIENT);
	set_signal_handler(&sc, signal_handler);
	send_message(ft_atoi(argv[1]), argv[2]);
}
