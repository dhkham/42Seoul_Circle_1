/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:58:50 by dkham             #+#    #+#             */
/*   Updated: 2023/01/24 20:57:22 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_x(unsigned int x, const char format)
{
	int		count;

	count = 0;
	if (format == 'x')
		write_hex(x, "0123456789abcdef", &count);
	else if (format == 'X')
		write_hex(x, "0123456789ABCDEF", &count);
	return (count);
}

int	print_p(unsigned long long p)
{
	int		count;

	if (write(1, "0x", 2) == -1)
		return (-1);
	count = 2;
	write_hex(p, "0123456789abcdef", &count);
	return (count);
}

int	write_hex(unsigned long long xp, char *hex_digits, int *count)
{
	if (xp / 16)
		if (write_hex(xp / 16, hex_digits, count) == -1)
			return (-1);
	if (write(1, &hex_digits[xp % 16], 1) == -1)
	{
		*count = -1;
		return (-1);
	}
	(*count)++;
	return (1);
}
