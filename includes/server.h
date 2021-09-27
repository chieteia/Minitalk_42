#ifndef SERVER_H
# define SERVER_H

# include "utils.h"

# define USAGE_SERVER "Usage : ./server"
# define DISCONNECT "Disconnected!!!"
# define ERROR_RESPONSE_TO_CLIENT "Error : Fail to send signal to client"

typedef struct s_server_vars
{
	int32_t	client_pid_bit;
	int32_t	client_pid_bit_size;
	uint8_t	message_pid_bit;
	uint8_t	message_pid_bit_size;
}				t_server_vars;

void	receive_bits(t_server_vars *vars, int signal);

#endif
