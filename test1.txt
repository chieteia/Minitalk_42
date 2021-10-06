#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//void	handler(int sig)
//{
//	write(1, "done\n", 5);
//}

//void	handler1(int sig)
//{
//	sleep(10);
//	write(1, "done1\n", 6);
//}

static int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n / 10)
		ft_putnbr_fd(n / 10, fd);
	else
		write(fd, "-", n < 0);
	write(fd, &"0123456789"[ft_abs(n % 10)], 1);
}


void print_bit(int num)
{
	if ((num / 2) == 0)
		return ;
	num /= 2;
	print_bit(num);
	ft_putnbr_fd(num % 2, 1);
}

void	handler(int sig)
{
	static	char c; // c = 0b00000000
	static	int num; // num = 0b000000000000000000000000000000000000000

	c = (c << 1) + (sig == SIGUSR1);
	num++;
	//print_bit((int)c);
	printf("%d\n", (int)c);
	if (num == 8)
	{
		write(1, &c, 1);
		write(1, "\nc(binary) = ", 14);
		print_bit((int)c);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask); // mask 初期化
	sigaddset(&sa.sa_mask, SIGUSR1); // maskの設定
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_handler = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("%d\n", getpid());
	while(1)
		pause(); // signalが来るまで待機
	return (0);
}

goal 10101011

c = 0b00000000

SIGUSR1 1 SIGUSR2 0

sig1
c = 0b00000000 + 1 ---> 0b00000001
c << 1 --> 0b00000010

sig2
c << 1 --> 0b00000100

sig1
c = 0b00000100 + 1 ---> 0b00000101
c << 1 --> 0b00001010
.
.
.

c = 0b10101011

c = 0b01001000
c << 1
c = 100100000
c << 1
c = 001000000
c >> 1
c = 000100000
