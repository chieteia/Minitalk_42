#include "../../includes/server.h"

//static void 	response_to_client(t_server_vars *vars, int received_signal)
//{
//	if (kill(vars->client_pid_bit, received_signal) == -1)
//		terminate(ERROR_RESPONSE_TO_CLIENT, 1);
//}

static void	receive_client_pid(t_server_vars *vars, int received_signal)
{
	vars->client_pid_bit <<= 1;
	if (received_signal == SIGUSR1)
		vars->client_pid_bit++;
	vars->client_pid_bit_size++;
	//if (vars->client_pid_bit_size == INT_BIT_SIZE)
		//response_to_client(vars, SIGUSR1);
}

static void	receive_message(t_server_vars *vars, int received_signal)
{
	vars->message_pid_bit <<= 1;
	if (received_signal == SIGUSR1)
		vars->message_pid_bit++;
	vars->message_pid_bit_size++;
	if (vars->message_pid_bit_size == CHAR_BIT_SIZE)
	{
		write(1, &vars->message_pid_bit, 1);
		if (vars->message_pid_bit == '\0')
		{
			vars->client_pid_bit = 0;
			vars->client_pid_bit_size = 0;
		}
		vars->message_pid_bit = 0;
		vars->message_pid_bit_size = 0;
	}
	//response_to_client(vars, received_signal);
}

/*
Server need to know client_pid to communicate with client.
*/
void	receive_bits(t_server_vars *vars, int received_signal)
{
	if (vars->client_pid_bit_size < INT_BIT_SIZE)
	{
		receive_client_pid(vars, received_signal);
		if (vars->client_pid_bit_size == INT_BIT_SIZE)
		{
			ft_putnbr_fd(vars->client_pid_bit, 1);
			write(1, "\n", 1);
		}
	}
	else
		receive_message(vars, received_signal);
}
