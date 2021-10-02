#ifndef UTILS_H
# define UTILS_H

# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <signal.h>

# define INT_BIT_SIZE 32
# define CHAR_BIT_SIZE 8
# define ERROR_SIGACTION "Error : Look at Sigaction()"

extern int	g_signal;

void	terminate(char *message, int status_code);
void	handle_signal(int signal);
void	set_signal(void);
void	set_signal_handler(struct sigaction *sa, \
							void (*handler)(int, siginfo_t*, void*));
void	set_terminate_handler(struct sigaction *sa, \
							void (*handler)(int, siginfo_t*, void*));

#endif
