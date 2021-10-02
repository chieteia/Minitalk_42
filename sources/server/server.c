#include "../../includes/server.h"

//#define EOT 4
# define BUF 10000

int	g_signal = 0;

void	put_char(int sig, siginfo_t *info, void *ucontext)
{
	static int	bit;
	static int	index;
	static char	c;
	static char	buf[BUF];

	(void)ucontext;
	(void)info;
	c = (c << 1) + (sig == SIGUSR1);
	bit++;
	if (bit == 8)
	{
		buf[index++] = c;
		if (c == '\0' || index == BUF)
		{
			write(1, buf, index);
			index = 0;
		}
		c = 0;
		bit = 0;
	//kill(info->si_pid, sig);
	}
}

void	exit_success(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	terminate(DISCONNECT, 0);
}

/*
Initilize server_vars to zero
*/
//static void	initialize_vars(t_server_vars *vars)
//{
//	vars->client_pid_bit = 0;
//	vars->client_pid_bit_size = 0;
//	vars->message_pid_bit = 0;
//	vars->message_pid_bit_size = 0;
//}

//void	receive_client_pid(t_server_vars *vars, int signal)
//{
//	vars->client_pid_bit <<= 1;
//	if (signal == SIGUSR1)
//		vars->client_pid_bit++;
//	vars->client_pid_bit_size++;
//}

//void	receive_bits(t_server_vars *vars, int signal)
//{
//	if (vars->client_pid_bit_size < INT_BIT_SIZE)
//	{
//		receive_client_pid(vars, signal);
//	}
//}

static void	check_argument(int argc)
{
	if (argc != 1)
		terminate(USAGE_SERVER, 1);
}

/*
Main program
*/
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
		pause();
	return (0);
}

//int	main(int argc, char **argv)
//{
//	t_server_vars	vars;

//	(void)argv;
//	check_argument(argc);
//	initialize_vars(&vars);
//	set_signal();
//	ft_putnbr_fd(getpid(), 1);
//	write(1, "\n", 1);
//	while (1)
//	{
//		//set_signal();
//		pause();
//		if (g_signal == SIGUSR1 || g_signal == SIGUSR2)
//			receive_bits(&vars, g_signal);
//		if (g_signal == SIGINT)
//			terminate(DISCONNECT, 0);
//	}
//	return (0);
//}

