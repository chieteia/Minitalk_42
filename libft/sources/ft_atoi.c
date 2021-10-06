/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoshihi <ntoshihi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 22:06:46 by ntoshihi          #+#    #+#             */
/*   Updated: 2021/10/04 22:06:46 by ntoshihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			minus;
	long		number;

	number = 0;
	minus = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		minus = (*str++ == '-');
	while ('0' <= *str && *str <= '9')
	{
		number = 10 * number + (*str++ - '0');
		if (number < LONG_MIN || LONG_MAX < number)
		{
			if (minus)
				number = 0;
			else
				number = -1;
			return (number);
		}
	}
	if (minus)
		number = -number;
	return ((int)number);
}
