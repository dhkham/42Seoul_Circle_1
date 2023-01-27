/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cspercent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:05:39 by dkham             #+#    #+#             */
/*   Updated: 2023/01/24 21:23:22 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(int c)
{
	int	count;

	count = write(1, &c, 1);
	if (count < 0)
		return (-1);
	return (count);
}

int	print_s(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		s = "(null)";
	while (*s)
	{
		if (write(1, s++, 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}

int	print_percent(void)
{
	int		count;

	count = write(1, "%", 1);
	if (count < 0)
		return (-1);
	return (count);
}
