#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
	if (kill(atoi(av[1]), SIGUSR1) < 0)
		write(1, "1", 1);
	if (kill(atoi(av[1]), SIGUSR1) < 0)
		write(1, "2", 1);
	if (kill(atoi(av[1]), SIGUSR1) < 0)
		write(1, "3", 1);
	if (kill(atoi(av[1]), SIGUSR1) < 0)
		write(1, "4", 1);
	if (kill(atoi(av[1]), SIGUSR1) < 0)
		write(1, "5", 1);
	if (kill(atoi(av[1]), SIGUSR1) < 0)
		write(1, "6", 1);
}