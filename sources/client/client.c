#include "../../includes/client.h"

int	g_signal;

void	signal_checker(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	(void)sig;
	write(1, "ok\n", 3);
	//if (g_signal == SIGUSR1)
	//	g_signal = SIGUSR2;
	//else
	//	g_signal = SIGUSR1;
}

//void	wait_server_response(void)
//{
//	sleep(100);
//	//if (g_signal == send_signal)
//	//	terminate(TIMEOUT, 1);
//}

static void send_bit(int server_pid, int send_signal)
{
	if (kill(server_pid, send_signal) == -1)
		terminate(ERROR_SEND_SIGNAL, 1);
}

void	send_char(pid_t server_pid, char c)
{
	int	n;
	int	send_signal;

	n = CHAR_BIT_SIZE;
	while (n--)
	{
		if ((c >> n) & 1)
			send_signal = SIGUSR1;
		else
			send_signal = SIGUSR2;
		g_signal = send_signal;
		send_bit(server_pid, send_signal);
		usleep(150);
		//wait_server_response();
	}
}

void	send_message(pid_t server_pid, char *msg)
{
	while (1)
	{
		send_char(server_pid, *msg);
		if (*msg == '\0')
			break ;
		msg++;
	}
}

//void	send_client_pid(pid_t servser_pid, pid_t client_pid)
//{
//	int	n;
//	int	send_signal;

//	n = INT_BIT_SIZE;
//	while (--n >= 0)
//	{
//		if ((client_pid >> n) & 1)
//			send_signal = SIGUSR1;
//		else
//			send_signal = SIGUSR2;
//		if (kill(servser_pid, send_signal) == -1)
//			terminate(ERROR_SEND_SIGNAL, 1);
//		usleep(50);
//	}
//	//wait_server_response();
//}

int	main(int ac, char **av)
{
	pid_t				server_pid;
	//struct sigaction	sc;

	if (ac != 3)
	{
		ft_putstr_fd(USAGE_CLIENT, 1);
		exit(1);
	}
	(void)ac;
	server_pid = ft_atoi(av[1]);
	//set_signal_handler(&sc, signal_checker);
	//send_client_pid(server_pid, client_pid);
	send_message(ft_atoi(av[1]), av[2]);
	terminate(SUCCESE_EXIT, 0);
}
