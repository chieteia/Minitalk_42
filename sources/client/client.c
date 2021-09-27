#include "../../includes/client.h"

int	g_signal;

void	send_char(pid_t server_pid, char c)
{
	int	n;
	int	send_signal;

	n = CHAR_BIT_SIZE;
	while (--n >= 0)
	{
		if ((c >> n) & 1)
			send_signal = SIGUSR1;
		else
			send_signal = SIGUSR2;
		if (kill(server_pid, send_signal) == -1)
			terminate(ERROR_SEND_SIGNAL, 1);
		usleep(50);
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

//void	wait_server_response(void)
//{
//	if (g_signal == SIGUSR1)

//}

void	send_client_pid(pid_t servser_pid, pid_t client_pid)
{
	int	n;
	int	send_signal;

	n = INT_BIT_SIZE;
	while (--n >= 0)
	{
		if ((client_pid >> n) & 1)
			send_signal = SIGUSR1;
		else
			send_signal = SIGUSR2;
		if (kill(servser_pid, send_signal) == -1)
			terminate(ERROR_SEND_SIGNAL, 1);
		usleep(50);
	}
	//wait_server_response();
}

int	main(int ac, char **av)
{
	pid_t		server_pid;
	pid_t		client_pid;

	if (ac != 3)
	{
		ft_putstr_fd(USAGE_CLIENT, 1);
		exit(1);
	}
	(void)ac;
	server_pid = ft_atoi(av[1]);
	client_pid = getpid();
	ft_putnbr_fd(client_pid, 1);
	send_client_pid(server_pid, client_pid);
	send_message(ft_atoi(av[1]), av[2]);
}
