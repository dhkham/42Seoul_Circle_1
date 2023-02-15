/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:01 by mkhan             #+#    #+#             */
/*   Updated: 2023/02/15 22:30:47 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	sign;
// 	int	result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-')
// 	{
// 		sign *= -1;
// 		i++;
// 	}
// 	else if (str[i] == '+')
// 		i++;
// 	while ('0' <= str[i] && str[i] <= '9')
// 	{
// 		result *= 10;
// 		result += str[i] - '0';
// 		i++;
// 	}
// 	return (result * sign);
// }

// write ft_atof function
// this should be a function that takes a string and returns a double

/*
 * ft_atof
 * @param str: a string to convert to a float
 * @return: the float value of the string
 */
int	ft_atof(const char *str)
{
	int i; /* The index of the string */
	int sign; /* The sign of the number */
	int result; /* The integer part of the number */
	int decimal; /* The decimal part of the number */

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		decimal = get_decimal(str, &i);
	return ((result + decimal) * sign);
}


int	get_decimal(const char *str, int *i)
{
	int decimal; /* The decimal part of the number */
	int decimal_count; /* The number of digits after the decimal point */

	decimal = 0;
	decimal_count = 0;
	*i += 1;
	while ('0' <= str[*i] && str[*i] <= '9')
	{
		decimal *= 10;
		decimal += str[*i] - '0';
		*i += 1;
		decimal_count++;
	}
	/* Make the decimal part a fraction */
	while (decimal_count > 0)
	{
		decimal /= 10;
		decimal_count--;
	}
	return (decimal);
}
