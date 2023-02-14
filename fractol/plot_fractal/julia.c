/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:25:32 by dkham             #+#    #+#             */
/*   Updated: 2023/02/14 19:18:32 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	init_julia(t_data *frctl, double x, double y)
{
	double	xtemp;

	frctl->iter = 0;
	frctl->max = 100;
	frctl->new_col = 0;
	xtemp = 0.0;
	while (x * x + y * y < 4 && frctl->iter < frctl->max)
	{
		xtemp = x * x - y * y;
		y = 2 * x * y - frctl->jy;
		x = xtemp + frctl->jx;
		frctl->iter = frctl->iter + 1;
	}
}

void	init(t_data *frctl, double *k, int i, int j)
{
	double	temp1;
	double	temp2;

	temp1 = 0.0;
	temp2 = 0.0;
	if (frctl->jx != 0)
	{
		temp1 = 1.5 * (i - frctl->width / 2);
		temp2 = (0.5 * frctl->zoom * frctl->width);
		k[0] = temp1 / temp2;
	}
	if (frctl->jy != 0)
	{
		temp1 = (j - frctl->height / 2);
		temp2 = (0.5 * frctl->zoom * frctl->height);
		k[1] = temp1 / temp2;
	}
}

void	julia(t_data *frctl)
{
	int		i[2];
	double	k[2];
	double	pts[2];

	i[0] = 0;
	pts[0] = 0.0;
	pts[1] = 0.0;
	k[0] = 0.0;
	k[1] = 0.0;
	while (i[0] < frctl->width)
	{
		i[1] = 0;
		while (i[1] < frctl->height)
		{
			init(frctl, k, i[0], i[1]);
			pts[0] = k[0]; //+ frctl->trans_x;
			pts[1] = k[1]; //+ frctl->trans_y;
			init_julia(frctl, pts[0], pts[1]);
			frctl->new_col = frctl->base_col * (frctl->iter
					/ (float)(frctl->max));
			my_mlx_pixel_put(frctl, i[0], i[1], frctl->new_col);
			i[1]++;
		}
		i[0]++;
	}			
}

