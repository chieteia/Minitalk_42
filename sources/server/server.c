#include "../../includes/server.h"

void	put_char(int sig, siginfo_t *info, void *ucontext)
{
	static int	bit;
	static char	c;

	(void)ucontext;
	(void)info;
	c = (c << 1) + (sig == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		c = 0;
		bit = 0;
	}
	usleep(100);
	kill(info->si_pid, sig);
	//g_signal = info->si_pid;
	//g_signal = g_signal << 1;
	//g_signal = g_signal + (sig == SIGUSR1);
	//printf("before : %d\n", g_signal);
}

void	exit_success(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	terminate(DISCONNECT, 0);
}

static void	check_argument(int argc)
{
	if (argc != 1)
		terminate(USAGE_SERVER, 1);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	struct sigaction	term;

	(void)argv;
	check_argument(argc);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	set_signal_handler(&sa, put_char);
	set_terminate_handler(&term, exit_success);
	while (1)
	{
		pause();
		//usleep(100);
		//printf("after : %d\n", (g_signal >> 1));
		//kill((g_signal >> 1), SIGUSR1);
	}
	return (0);
}

//client ---> sig1 ---> server
//client <--- sig1 <--- server