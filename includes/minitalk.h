/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoshihi <ntoshihi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:09:50 by ntoshihi          #+#    #+#             */
/*   Updated: 2021/10/08 10:25:42 by ntoshihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <signal.h>

# define INT_BIT_SIZE 32
# define CHAR_BIT_SIZE 8

//server
# define SERVER 0
# define USAGE_SERVER "USAGE : ./server\n"
# define DISCONNECT "\nDisconnected!!!\n"
# define ERROR_SEND_ACK "ERROR : Fail to send signal to client\n"
# define SUCCESS_MSG_SERVER "\nSuccessfully recieved string from client\n"

//client
# define CLIENT 1
# define INVALID_PID "ERROR : Invalid server_PID\n"
# define USAGE_CLIENT "USAGE : ./client [server_PID] [STRING should be sent]\n"
# define ERROR_SEND_SIGNAL "ERROR : Fail to send signal to server\n"
# define TIMEOUT "TIMEOUT : No response from server\n"
# define SUCCESS_MSG_CLIENT "Successfully sent string to server\n"
# define UNMATCHED_SIGNL "ERROR : Received signal differ from sent one\n"

//sigaction
# define ERROR_SIGACTION "ERROR : Look at Sigaction()\n"

//SIGNAL
# define WAITING_SIGNAL 0

//ACK
# define WAITING_ACK 0
# define RECIEVED_ACK 1

//color settings
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"

typedef struct s_server_vars
{
	int32_t	client_pid_bit;
	int32_t	client_pid_bit_size;
	uint8_t	message_pid_bit;
	uint8_t	message_pid_bit_size;
}				t_server_vars;

void	ft_putstr_color(char *msg, char *color);
void	terminate(char *message, char *color, int status_code);
void	set_signal_handler(struct sigaction *sa, \
							void (*handler)(int, siginfo_t*, void*));
void	check_arguments(int argc, char **argv, int mode);

#endif
