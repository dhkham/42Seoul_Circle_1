/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:43:12 by dkham             #+#    #+#             */
/*   Updated: 2023/01/08 18:29:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_flags *flags, int c)
{
	int	count;

	count = 0;
	if (flags->minus == 1)
	{
		count += write(1, &c, 1);
		while (flags->width-- > 1)
			count += write(1, " ", 1);
	}
	else
	{
		while (flags->width-- > 1)
			count += write(1, " ", 1);
		count += write(1, &c, 1);
	}
	return (count);
}

// consider 0 UB case
int	print_s(t_flags *flags, char *s)
{
	int	count_and_space[2];

	count_and_space[0] = 0;
	if (s == NULL)
		s = "(null)";
	if (flags->precision != 0 && flags->minus == 1)
	{
		while (*s && flags->precision--)
			count_and_space[0] += write(1, s++, 1);
		while (flags->width > count_and_space[0])
			count_and_space[0] += write(1, " ", 1);
	}
	else
	{
		count_and_space[1] = (int)ft_strlen(s);
		if (flags->dot == 1 && flags->precision == 0)
			count_and_space[1] = 0;
		else if (flags->dot == 1 && flags->precision < (int)ft_strlen(s))
			count_and_space[1] = flags->precision;
		while (flags->width-- > count_and_space[1])
			count_and_space[0] += write(1, " ", 1);
		while (*s && flags->precision--)
			count_and_space[0] += write(1, s++, 1);
	}
	return (count_and_space[0]);
}

// int print_x(t_flags *flags, unsigned int x)
// {
//     int count;
//     char *str;

//     count = 0;
//     if (flags->precision == 0 && x == 0)
//         return (0);
//     str = ft_itoa_base(x, 16);
//     if (flags->hash == 1 && x != 0) // # : 16진수 앞에 0x 붙이기
//     {
//         write(1, "0x", 2);
//         count += 2;
//     }
//     while (flags->precision-- > (int)ft_strlen(str))
//     {
//         write(1, "0", 1);
//         count++;
//     }
//     while (*str)
//     {
//         write(1, str++, 1);
//         count++;
//     }
//     return (count);
// }

// int print_uu(t_flags *flags, unsigned int u)
// {
//     int count;
//     char *str;

//     count = 0;
//     if (flags->precision == 0 && u == 0)
//         return (0);
//     str = ft_itoa_base(u, 10);
//     while (flags->precision-- > (int)ft_strlen(str))
//     {
//         write(1, "0", 1);
//         count++;
//     }
//     while (*str)
//     {
//         write(1, str++, 1);
//         count++;
//     }
//     return (count);
// }

// int print_p(t_flags *flags, unsigned long long p)
// {
//     int count;

//     count = 0;
//     if (flags->minus == 1) // left justify
//     {
//         write(1, "0x", 2);
//         count += 2;
//         count += print_x(flags, p); // write address first, then print spaces depending on width
//         while (flags->width-- > count)
//         {
//             write(1, " ", 1);
//             count++;
//         }
//     }
//     else // right justify (default)
//     {
//         while (flags->width-- > count) // flags->width-- > length of address + 2
//         {
//             write(1, " ", 1);
//             count++;
//         }
//         write(1, "0x", 2);
//         count += 2;
//         count += print_x(flags, p); // print spaces first depending on width, then write address
//     }
//     return (count);
// }

int	print_id(t_flags *flags, int d)
{
	int		count;
	int		spaces;
	char	*str;
	int		strlen;

	count = 0;
	str = ft_itoa_base(d, 10);
	strlen = ft_strlen(str);
	// if (flags->plus == 1 && d >= 0)
	// 	strlen++;
	if (flags->space == 1)
		count += write(1, " ", 1);
	if (flags->minus == 1)
	{
		if (flags->plus == 1 && d >= 0)
			count += write(1, "+", 1);
		if (d < 0)
			count += write(1, "-", 1);
		count += print_int(flags, d, str, strlen);
		while (flags->width > count)
			count += write(1, " ", 1);
	}
	else
	{
		if (flags->dot == 1 && flags->minus == 0) // ft_printf("ft:%08.5i\n", 8375);
			spaces = flags->width - flags->precision;
		else
			spaces = flags->width - strlen;
		// while (spaces > 0 && flags->zero == 0)
		// {
		// 	count += write(1, " ", 1);
		// 	spaces--;
		// }
		// while (spaces > 0 && flags->zero == 1)
		// {
		// 	count += write(1, "0", 1);
		// 	spaces--;
		// }
		if (flags->zero == 1 && flags->dot == 0)
			while (spaces-- > 0)
				count += write(1, "0", 1);
		else
			while (spaces-- > 0)
				count += write(1, " ", 1);
				
		
		if (flags->plus == 1 && d >= 0)
			count += write(1, "+", 1);
		if (d < 0)
			count += write(1, "-", 1);
		count += print_int(flags, d, str, strlen);
	}
	free(str);
	return (count);
}

int	print_int(t_flags *flags, int d, char *str, int strlen)
{
	int		count;

	count = 0;
	if (flags->precision == 0 && d == 0)
		return (0);
	if (d < 0 && flags->dot == 1)
	{
		str++;
		strlen--;
	}
	else if (d < 0)
		str++;
	if (flags->dot == 1)
	{
		while (flags->precision > strlen)
		{
			count += write(1, "0", 1);
			strlen++;
		}
	}
	else
	{
		while (flags->width > strlen && flags->zero == 1)
		{
			count += write(1, "0", 1);
			strlen++;
		}
	}
	// while (flags->precision > strlen && flags->width > strlen) // 0 출력 // 7>3 12>3
	// {
	// 	count += write(1, "0", 1);
	// 	strlen++;
	// }
	while (*str)
		count += write(1, str++, 1); // 문자 출력
	return (count);
}

int	get_length(int value, int base)
{
	int	length;

	length = 0;
	if (value == 0)
		return (1);
	if (value < 0)
		++length;
	while (value != 0)
	{
		value = value / base;
		length++;
	}
	return (length);
}

char	*ft_itoa_base(int value, int base)
{
	int		neg;
	char	*num;
	int		len;

	neg = 0;
	len = get_length(value, base);
	num = malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (value < 0)
	{
		value = value * -1;
		neg = 1;
	}
	while (len--)
	{
		num[len] = "0123456789ABCDEF"[value % base];
		value = value / base;
	}
	if (neg == 1)
		num[0] = '-';
	return (num);
}
// int print_u(t_flags *flags, unsigned int u)
// {
//     int count;

//     count = 0;
//     if (flags->minus == 1) // - : 왼쪽 정렬
//     {
//         count += print_u(flags, u);
//         while (flags->width-- > count)
//         {
//             write(1, " ", 1);
//             count++;
//         }
//     }
//     else
//     {
//         while (flags->width-- > count)
//         {
//             write(1, " ", 1);
//             count++;
//         }
//         count += print_u(flags, u);
//     }
//     return (count);
// }

// int	print_xx(t_flags *flags, unsigned int x)
// {
// 	int count;

// 	count = 0;
// 	if (flags->minus == 1) // - : 왼쪽 정렬
// 	{
// 		count += print_x(flags, x);
// 		while (flags->width-- > count)
// 		{
// 			write(1, " ", 1);
// 			count++;
// 		}
// 	}
// 	else
// 	{
// 		while (flags->width-- > count)
// 		{
// 			write(1, " ", 1);
// 			count++;
// 		}
// 		count += print_x(flags, x);
// 	}
// 	return (count);
// }

int	print_percent(t_flags *flags)
{
	int		count;
	char	*space_or_zero;

	count = 0;
	if (flags->zero == 1)
		space_or_zero = "0";
	else
		space_or_zero = " ";
	if (flags->minus == 1)
	{
		write(1, "%", 1);
		count++;
		while (flags->width-- > count)
			count += write(1, " ", 1);
	}
	else
	{
		while (flags->width-- > 1)
			count += write(1, space_or_zero, 1);
		count += write(1, "%", 1);
	}
	return (count);
}
