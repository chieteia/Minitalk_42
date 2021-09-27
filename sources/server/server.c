#include "../../includes/server.h"

//#define EOT 4

int	g_signal = 0;

/*
Initilize server_vars to zero
*/
static void	initialize_vars(t_server_vars *vars)
{
	vars->client_pid_bit = 0;
	vars->client_pid_bit_size = 0;
	vars->message_pid_bit = 0;
	vars->message_pid_bit_size = 0;
}

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
	t_server_vars	vars;

	(void)argv;
	check_argument(argc);
	initialize_vars(&vars);
	set_signal();
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
	{
		//set_signal();
		pause();
		if (g_signal == SIGUSR1 || g_signal == SIGUSR2)
			receive_bits(&vars, g_signal);
		if (g_signal == SIGINT)
			terminate(DISCONNECT, 0);
	}
	return (0);
}
