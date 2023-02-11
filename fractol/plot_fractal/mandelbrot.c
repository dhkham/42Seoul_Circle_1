/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:25:28 by dkham             #+#    #+#             */
/*   Updated: 2023/02/11 20:13:36 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_data *frctl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < frctl->width)
	{
		while (j < frctl->height)
		{
			get_c(frctl, i, j); // c_a, c_b 값 구하기
			init_mandelbrot(frctl); // iter 값 구하기
			// iter에 따라 색상 결정 new_col // (float)(frctl->max)??
			frctl->new_col = frctl->base_col * (frctl->iter / (frctl->max)); // 공식 다른 사람 어케 했는지?
			my_mlx_pixel_put(frctl, i, j, frctl->new_col); // 픽셀에 색상 채우기
			j++;
		}
		i++;
	}
}

void	get_c(t_data *frctl, int x, int y) // static?? 
{
	// c_a, c_b: 복소 평면의 좌표
	frctl->c_a = (x - (frctl->width / 2)) / (frctl->width / 4);
	frctl->c_b = -(y - (frctl->height / 2)) / (frctl->height / 4);
}

void	init_mandelbrot(t_data *frctl)
{
	double	x;
	double	y;
	double	tmp;

	frctl->iter = 0;
	frctl->max = 10000; // 암거나 해도 됨?
	frctl->new_col = 0;
	tmp = 0.0;
	x = 0.0;
	y = 0.0;
	while (x * x + y * y <= 2 * 2 && frctl->iter < frctl->max)
	{// 수렴 시 iter 값이 max_iter에 도달. 발산 시 iter 값에 따라 색 다르게 표현함.
		tmp = x * x - y * y + frctl->c_a;
		y = 2 * x * y + frctl->c_b; // yn+1 = 2xy + c_b
		x = tmp; 					// xn+1 = x^2 - y^2 + c_a
		frctl->iter++;
	}
}
