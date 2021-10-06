/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoshihi <ntoshihi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 02:55:56 by ntoshihi          #+#    #+#             */
/*   Updated: 2021/10/06 22:03:21 by ntoshihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

static int	g_signal = WAITING_SIGNAL;

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	g_signal = (info->si_pid << 1) + (sig == SIGUSR1);
}

static void	put_packet(int8_t *c, int8_t *bit)
{
	if (*c == 0x4)
		ft_putstr_color(SUCCESS_MSG_SERVER, GREEN);
	else
		write(1, c, 1);
	*c = 0;
	*bit = 0;
}

static void	recieving_packet(void)
{
	int		client_pid;
	int8_t	bit;
	int8_t	c;

	bit = 0;
	c = 0;
	while (1)
	{
		while (g_signal == WAITING_SIGNAL)
			;
		client_pid = (g_signal >> 1);
		c = (c << 1) + (g_signal & 1);
		g_signal = WAITING_SIGNAL;
		if (++bit == 8)
			put_packet(&c, &bit);
		if (kill(client_pid, SIGUSR1) == -1)
			terminate(ERROR_SEND_ACK, RED, 1);
	}
}

static void	print_server_pid(void)
{
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd("SERVER_PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd(RESET, 1);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	check_arguments(argc, argv, SERVER);
	set_signal_handler(&sa, signal_handler);
	print_server_pid();
	recieving_packet();
	return (0);
}
