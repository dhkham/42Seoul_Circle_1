/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:53:37 by dkham             #+#    #+#             */
/*   Updated: 2023/01/25 20:05:35 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = printparse(format, ap);
	va_end(ap);
	return (count);
}

int	printparse(const char *format, va_list ap)
{
	int	count;
	int	write_count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			write_count = ft_parse(format, ap);
		}
		else
			write_count = write(1, format, 1);
		if (write_count < 0)
			return (-1);
		count += write_count;
		format++;
	}
	return (count);
}

int	ft_parse(const char *format, va_list ap)
{
	int		count;

	count = 0;
	if (ft_strchr("cspdiuxX%", *format))
		count = ft_parse_type(format, ap);
	if (count < 0)
		return (-1);
	return (count);
}

int	ft_parse_type(const char *format, va_list ap)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count = print_c(va_arg(ap, int));
	else if (*format == 's')
		count = print_s(va_arg(ap, char *));
	else if (*format == '%')
		count = print_percent();
	else if (*format == 'i' || *format == 'd')
		count = print_id(va_arg(ap, int));
	else if (*format == 'u')
		count = print_u(va_arg(ap, unsigned int));
	else if (*format == 'x' || *format == 'X')
		count = print_x(va_arg(ap, unsigned int), *format);
	else if (*format == 'p')
		count = print_p(va_arg(ap, unsigned long long));
	if (count < 0)
		return (-1);
	return (count);
}
