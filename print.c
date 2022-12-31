/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:43:12 by dkham             #+#    #+#             */
/*   Updated: 2022/12/31 21:11:52 by dkham            ###   ########.fr       */
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
	int num_spaces;
	
    count = 0;
	if (s == NULL)
	{
		s = "(null)";
		num_spaces = 6;
	}
    if (flags->minus == 1) // left justify
    {
        while (*s && flags->precision--) // write s first, considering precision(max length)
        {
            write(1, s++, 1);
            count++; //3
        }
        while (flags->width > count) // add spaces after s, considering width(only if width > count)
        {
            write(1, " ", 1); //13
            count++;
        }
    }
    else // right justify (default)
    {
		if (flags->precision >= (int)ft_strlen(s) || flags->precision == -1)
			num_spaces = (int)ft_strlen(s); // 11.6 or 11. : 문자열만큼 남겨두고 공백 출력
		if (flags->precision < (int)ft_strlen(s) && flags->precision != -1)
			num_spaces = flags->precision; // 11.4 : 정밀도만큼 남겨두고 공백 출력
		if (flags->precision == 0) //3.0 : 너비만큼 공백출력
			num_spaces = 0;
		while (flags->width > num_spaces++)
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

int		get_length(int value, int base)
{
	int	ret;

	ret = 0;
	//("value: %d", value);
	if (value == 0)
		return (1);
	if (value < 0 && base == 10)
		++ret;
	while (value != 0)
	{
		value = value / base;
		ret++;
	}
	return (ret);
}

char	*ft_itoa_base(int value, int base)
{
	int neg;
	char *num;
	int	len;
	long  value_cpy;
	char	buff[16] = "0123456789ABCDEF";
	
	//printf("value: %d", value);
	neg = 0;
	len = get_length(value, base);
	num = (char *)malloc(sizeof(*num) * (len));
	if (!num)
		return (NULL);
	num[len] = '\0';
	value_cpy = value;
	if (value_cpy < 0)
	{
		if (base == 10)
			neg = 1;
		value_cpy = value_cpy * -1;
	}
	while (--len)
	{
		num[len] = buff[value_cpy % base];
		value_cpy = value_cpy / base;
	}
	if (neg == 1)
		num[0] = '-';
	else
		num[len] = buff[value_cpy % base];
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
