/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:43:12 by dkham             #+#    #+#             */
/*   Updated: 2023/01/12 22:58:07 by dkham            ###   ########.fr       */
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
	if (flags->space == 1 && d >= 0 && strlen >= flags->width)
		count += write(1, " ", 1);
	if (flags->minus == 1) // 왼쪽 정렬 (부호-숫자(0패딩)-공백)
	{
		count += print_int(flags, d, str, strlen); // 부호 - 숫자 출력(0패딩)
		while (flags->width > count)
			count += write(1, " ", 1); // 마지막에 끝에 공백 출력
	}
	else                   // 오른쪽 정렬 (공백-부호-숫자(0패딩))
	{
		if (flags->dot == 1 && flags->precision >= strlen && (flags->plus == 1 || d < 0)) // dot == 1 이고 부호(+혹은-)가 붙는 경우에는 공백 하나 덜 출력 해야한다
			spaces = flags->width - flags->precision - 1;
		else if (flags->dot == 1 && flags->precision >= strlen)
			spaces = flags->width - flags->precision;
		else if (flags->dot == 1 && (flags->precision == 0 || flags->precision == -1) && d == 0)
			spaces = flags->width;
		else if (flags->plus == 1 && d >= 0)
			spaces = flags->width - strlen - 1;
		else
			spaces = flags->width - strlen;
		while (spaces-- > 0 && ((flags->zero == 1 && flags->dot == 1) || flags->zero != 1)) // 1. zero 있고 dot 있으면 공백 출력 2. zero 없으면 공백 출력
			count += write(1, " ", 1);
		count += print_int(flags, d, str, strlen); // 부호와 숫자 출력(0패딩)
	}
	if (ft_strncmp(str, "-2147483648", 11) != 0)
		free(str);
	return (count);
}
// 왼: 부호-(0패딩)숫자-공백 // 오: 공백-부호-(0패딩)숫자
// print_int는 부호-숫자(0패딩) 담당
int	print_int(t_flags *flags, int d, char *str, int strlen)
{
	int		count;
	int		zeros;

	count = 0;
	if (flags->precision == 0 && d == 0) // precision 0이고 d가 0이면 아무것도 출력하지 않음
		return (0);
	// 부호 출력
	if (flags->plus == 1 && d >= 0)
		count += write(1, "+", 1);
	if (d < 0)
	{
		count += write(1, "-", 1);
		str++; // 이미 함수 들어오기 전에 부호는 찍은 상태이므로 str++로 부호 부분 넘어감
	}
	// 0 패딩 출력
	// if (d < 0)
	// 	str++; // 이미 함수 들어오기 전에 부호는 찍은 상태이므로 str++로 부호 부분 넘어감
	if (d < 0 && flags->dot == 1)
		strlen--; // 0은 precision - (부호 제외 순수 strlen) 만큼 찍어야 하므로, d가 음수이고 precision이 있는 경우 strlen-1
	if (flags->dot == 1)
		zeros = flags->precision - strlen;
	else
		zeros = flags->width - strlen;
	while (zeros > 0 && (flags->zero == 1 || flags->dot == 1))
	{
		count += write(1, "0", 1);
		zeros--;
	}
	// 실제 숫자 파트 출력
	while (*str)
		count += write(1, str++, 1);
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

    if (value == -2147483648 && base == 10)
        return ("-2147483648");
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
