/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:26:01 by mkhan             #+#    #+#             */
/*   Updated: 2023/02/16 20:13:24 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	skip_whitespace(const char *str, int i)
{
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	judge_sign(const char *str, int i, int *sign)
{
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

void	handle_decimal(const char *str, int i, double *decimal)
{
	int	count;

	count = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		*decimal *= 10;
		*decimal += str[i] - '0';
		i++;
		count++;
	}
	if (str[i] == '.')
	{
		printf("Error: invalid input");
		exit(1);
	}
	if (str[i] != '\0' && ft_isdigit(str[i]) == 0)
		exit(1);
	while (count--)
		*decimal /= 10;
}

double	ft_atod(const char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0;
	decimal = 0;
	sign = 1;
	i = 0;
	i = skip_whitespace(str, i);
	i = judge_sign(str, i, &sign);
	if (str[i] != '\0' && ft_isdigit(str[i]) == 0)
		exit(1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		handle_decimal(str, i, &decimal);
	}
	return ((result + decimal) * sign);
}
