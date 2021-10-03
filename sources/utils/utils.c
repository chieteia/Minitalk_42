#include "../../includes/utils.h"

/*
Print message and Exit()
*/
void	terminate(char *message, int status_code)
{
	ft_putstr_fd(message, 1);
	exit(status_code);
}

void	set_signal_handler(struct sigaction *sa, \
							void (*handler)(int, siginfo_t*, void*))
{
	ft_bzero(sa, sizeof(struct sigaction));
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	//sigaddset(&sa->sa_mask, SIGINT);
	//sigaddset(&sa->sa_mask, SIGTERM);
	sa->__sigaction_u.__sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa, NULL) == FAILED)
		terminate(ERROR_SIGACTION, 1);
	if (sigaction(SIGUSR2, sa, NULL) == FAILED)
		terminate(ERROR_SIGACTION, 1);
	//if (sigaction(SIGINT, sa, NULL) == FAILED)
	//	terminate(ERROR_SIGACTION, 1);
	//if (sigaction(SIGTERM, sa, NULL) == FAILED)
	//	terminate(ERROR_SIGACTION, 1);
}

void	set_terminate_handler(struct sigaction *sa, \
							void (*handler)(int, siginfo_t*, void*))
{
	ft_bzero(sa, sizeof(struct sigaction));
	sigemptyset(&sa->sa_mask);
	//sigaddset(&sa->sa_mask, SIGUSR1);
	//sigaddset(&sa->sa_mask, SIGUSR2);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGTERM);
	sa->__sigaction_u.__sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	//if (sigaction(SIGUSR1, sa, NULL) == FAILED)
	//	terminate(ERROR_SIGACTION, 1);
	//if (sigaction(SIGUSR2, sa, NULL) == FAILED)
	//	terminate(ERROR_SIGACTION, 1);
	if (sigaction(SIGINT, sa, NULL) == FAILED)
		terminate(ERROR_SIGACTION, 1);
	if (sigaction(SIGTERM, sa, NULL) == FAILED)
		terminate(ERROR_SIGACTION, 1);
}
