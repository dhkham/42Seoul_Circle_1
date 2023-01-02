/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:02:40 by dkham             #+#    #+#             */
/*   Updated: 2023/01/02 21:30:44 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// hi bye
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = ft_vprintf(format, ap);
	va_end(ap);
	return (count);
}

int	ft_vprintf(const char *format, va_list ap)
{
	int	count;

	count = 0;
	while (*format) // *format is the first character of the string.
	{
		if (*format == '%')
		{
			format++;
			count += ft_parse(&format, ap); // &format is the address of the first character of the string.
		}
		else
			count += write(1, format, 1);
		format++;
	}
	return (count);
}

int	ft_parse(const char **format, va_list ap)
{
	t_flags	flags;
	int		count;

	count = 0;
	ft_init_flags(&flags);
	while (ft_strchr("-0.# +123456789", **format))
		ft_parse_flags(&flags, format);
	if (ft_strchr("cspdiuxX%", **format))
		count += ft_parse_type(&flags, format, ap);
	return (count);
}

void	ft_parse_flags(t_flags *flags, const char **format)
{
	if (**format == '-')
		flags->minus = 1;
	else if (**format == '0')
		flags->zero = 1;
	else if (**format == '.')
	{
		flags->dot = 1;
		(*format)++;
		flags->precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
		(*format)--;
	}
	else if (**format == '#')
		flags->hash = 1;
	else if (**format == ' ')
		flags->space = 1;
	else if (**format == '+')
		flags->plus = 1;
	else if (ft_isdigit(**format))
	{
		flags->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
		(*format)--;
	}
	(*format)++;
}

int	ft_parse_type(t_flags *flags, const char **format, va_list ap)
{
	int	count;

	count = 0;
	if (**format == 'c')
		count += print_c(flags, va_arg(ap, int));
	else if (**format == 's')
		count += print_s(flags, va_arg(ap, char *));
<<<<<<< Updated upstream
=======
		//printf("")
	}
>>>>>>> Stashed changes
	// else if (**format == 'p')
    //     count += print_p(flags, va_arg(ap, unsigned long long));
	else if (**format == 'i' || **format == 'd')
		count += print_id(flags, va_arg(ap, int));
	// else if (**format == 'u')
    //     count += print_u(flags, va_arg(ap, unsigned int));
    // else if (**format == 'x')
    //     count += print_x(flags, va_arg(ap, unsigned int));
    // else if (**format == 'X')
    //     count += print_xx(flags, va_arg(ap, unsigned int));
	else if (**format == '%')
		count += print_percent(flags);
	return (count);
}
