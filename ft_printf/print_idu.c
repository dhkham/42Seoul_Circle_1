/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_idu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:33:28 by dkham             #+#    #+#             */
/*   Updated: 2023/01/25 20:05:00 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_id(int d)
{
	long long	num;
	int			count;

	count = 0;
	num = (long long)d;
	if (num < 0)
	{
		num *= -1;
		if (write(1, "-", 1) == -1)
			return (-1);
		count++;
	}
	if (write_idu(num, &count) == -1)
		return (-1);
	return (count);
}

int	print_u(unsigned int u)
{
	int			count;

	count = 0;
	write_idu(u, &count);
	return (count);
}

int	write_idu(long long idu, int *count)
{
	long long	num;

	if (idu / 10)
		if (write_idu(idu / 10, count) == -1)
			return (-1);
	num = idu % 10 + '0';
	if (write(1, &num, 1) == -1)
	{
		*count = -1;
		return (-1);
	}
	(*count)++;
	return (1);
}
