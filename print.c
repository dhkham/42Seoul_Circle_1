/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:43:12 by dkham             #+#    #+#             */
/*   Updated: 2023/01/01 16:47:03 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(t_flags *flags, int c)
{
	int	count;

	count = 0;
	if (flags->minus == 1)
	{
		write(1, &c, 1);
		count++;
		while (flags->width-- > 1)
		{
			write(1, " ", 1);
			count++;
		}
	}
	else
	{
		while (flags->width-- > 1)
		{
			write(1, " ", 1);
			count++;
		}
		write(1, &c, 1);
		count++;
	}
	return (count);
}

int	print_s(t_flags *flags, char *s)
{
	int	count;
	int	num_spaces;

	count = 0;
	if (s == NULL)
	{
		s = "(null)";
		num_spaces = 6;
	}
	if (flags->minus == 1)
	{
		while (*s && flags->precision--)
		{
			write(1, s++, 1);
			count++;
		}
		while (flags->width > count)
		{
			write(1, " ", 1);
			count++;
		}
	}
	else
	{
		if (flags->precision >= (int)ft_strlen(s) || flags->precision == -1)
			num_spaces = (int)ft_strlen(s);
		if (flags->precision < (int)ft_strlen(s) && flags->precision != -1)
			num_spaces = flags->precision;
		if (flags->precision == 0)
			num_spaces = 0;
		while (flags->width > num_spaces++)
		{
			write(1, " ", 1);
			count++;
		}
		while (*s && flags->precision--)
		{
			write(1, s++, 1);
			count++;
		}
	}
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
	long	value_cpy;

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
	char *str;

	count = 0;
	if (flags->plus == 1)
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
        if (d < 0)
        {
            write(1, "-", 1);
            count++;
        }
		count += print_int(flags, d);
        while (flags->width > ++count)
            write(1, " ", 1);
    }
    else // right justify (default)
    {
		str = ft_itoa_base(d, 10);
		count = ft_strlen(str); // '-'까지 포함한 길이
		//printf("count : %d\n", count);
		if (flags->precision != -1 && d < 0)
			count = flags->precision + 1;
		while (flags->width > count && flags->zero != 1)
		{
            write(1, " ", 1);
			count++;
		}
		//printf("count : %d\n", count);
        if (d < 0)
		{
			write(1, "-", 1);
			count++;
		}
        count += print_int(flags, d);
		count -= ft_strlen(str);
		free(str); // ???
    }
    return (count);
}

int print_int(t_flags *flags, int d) // 실제 숫자 출력 (+ precision 고려해 0 추가)
{
    int count;
    char *str;

    count = 0;
    if (flags->precision == 0 && d == 0) // printf("pf:%10.0d\n", 0);
        return (0);
    str = ft_itoa_base(d, 10);
	//printf("strlen:%d\n", ft_strlen(str));
    while (flags->precision-- > (int)ft_strlen(str) || flags->width-- > (int)ft_strlen(str)) // 0 추가
	{
		write(1, "0", 1);
		count++;
	}
	//printf("%d", d);
	// if (d < 0)
    //     d *= -1;
    while (*++str)
    {
        write(1, str, 1);
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
