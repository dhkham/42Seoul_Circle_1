/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:43:12 by dkham             #+#    #+#             */
/*   Updated: 2022/12/30 21:03:40 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int print_c(t_flags *flags, int c) // UB: precision, 0, +, #, space
{
    int count;

    count = 0;
    if (flags->minus == 1) // left justify
    {
        write(1, &c, 1); // print c first, then print spaces depending on width
        count++;
        while (flags->width-- > 1) // if width is 3, print 2 spaces after c
        {
            write(1, " ", 1);
            count++;
        }
    }
    else // right justify (default)
    {
        while (flags->width-- > 1) // print spaces first depending on width, then print c
        {
            write(1, " ", 1);
            count++;
        }
        write(1, &c, 1);
        count++;
    }
    return (count);
}

int print_s(t_flags *flags, char *s) // UB: 0, +, #, space (and empty string?)
{
    int count;

    count = 0;
    if (s == NULL)
        s = "";
    if (flags->minus == 1) // left justify
    {
        while (*s && flags->precision--) // write s first, considering precision(max length)
        {
            write(1, s++, 1);
            count++;
        }
        while (flags->width-- > count) // add spaces after s, considering width(only if width > count)
        {
            write(1, " ", 1);
            count++;
        }
    }
    else // right justify (default)
    {
		// Hello 출력
		// 11.4 => 공백 7칸, 출력 4칸 (flags->precision >= ft_strlen(s): width - strlen 만큼 공백 출력)
		// 11.6 => 공백 6칸, 출력 5칸 (flags->precision < ft_strlen(s): width - precision 만큼 공백 출력)
		int var_for_space;
		if (flags->precision >= (int)ft_strlen(s))
			var_for_space = (int)ft_strlen(s);
		else
			var_for_space = flags->precision;
		while (flags->width-- > var_for_space)
		{
        	write(1, " ", 1);
        	count++;
		}
        while (*s && flags->precision--) // write s after adding spaces
        {
            write(1, s++, 1);
            count++;
        }
    }
    return (count);
}

// 여기부터 보기!

// print_x: print an integer value as a hexadecimal (base 16) number.
// print_p calls print_x +add "0x" in front

int nbrlen(long n, int base)
{
    int len;

    len = 0;
    if (n == 0)
        return (1);
    while (n)
    {
        n /= base;
        len++;
    }
    return (len);
}

// integer to string (+ base conversion to octal, decimal, hexadecimal)
char    *ft_itoa_base(unsigned int x, int base)
{
	char    *str;
	int     len;
	char    *base_str;

	base_str = "0123456789abcdef";
	len = nbrlen(x, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	while (len--)
	{
		str[len] = base_str[x % base];
		x /= base;
	}
	return (str);
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

int print_id(t_flags *flags, int d)
{
    int count;
	char *	space_or_zero;

	count = 0;
	if (flags->zero == 1)
		space_or_zero = "0";
	else
		space_or_zero = " ";
	if (d < 0)
    {
        write(1, "-", 1);
        count++;
	}
	else if (flags->plus == 1)
	{
		write(1, "+", 1);
		count++;
	}
	if (flags->space == 1)
	{
		write(1, " ", 1);
		count++;
	}
    if (flags->minus == 1) // - : left justify
    {
        count += print_int(flags, d);
        while (flags->width-- > count)
        {
            write(1, " ", 1);
            count++;
        }
    }
    else // right justify (default)
    {
        while (flags->width-- > count)
        {
            write(1, space_or_zero, 1);
            count++;
        }
        if (d < 0)
        {
            write(1, "-", 1);
            count++;
        }
        count += print_int(flags, d);
    }
    return (count);
}

int print_int(t_flags *flags, int d)
{
    int count;
    char *str;

    count = 0;
    if (flags->precision == 0 && d == 0)
        return (0);
    if (d < 0)
        d *= -1;
    str = ft_itoa_base(d, 10);
    while (flags->precision-- > (int)ft_strlen(str))
    {
        write(1, "0", 1);
        count++;
    }
    while (*str)
    {
        write(1, str++, 1);
        count++;
    }
    return (count);
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
	int count;
	char *	space_or_zero;

	count = 0;
	if (flags->zero == 1)
		space_or_zero = "0";
	else
		space_or_zero = " ";
	if (flags->minus == 1) // - : left justify
	{
		write(1, "%", 1);
		count++;
		while (flags->width-- > count)
		{
			write(1, " ", 1);
			count++;
		}
	}
	else
	{
		while (flags->width-- > 1) // reserve one space for "%"
		{
			write(1, space_or_zero, 1);
			count++;
		}
		write(1, "%", 1);
		count++;
	}
	return (count);
}
