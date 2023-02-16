/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:38:50 by dkham             #+#    #+#             */
/*   Updated: 2023/02/16 22:06:59 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	burningship(t_data *frctl)
{
	int	i;
	int	j;

	i = 0;
	while (i < frctl->w)
	{
		j = 0;
		while (j < frctl->h)
		{
			get_c_burningship(frctl, i, j);
			get_iter_burningship(frctl);
			if (frctl->iter == frctl->max)
				frctl->new_col = 0x00000000;
			else
				frctl->new_col = frctl->base_col * frctl->iter;
			my_mlx_pixel_put(frctl, i, j, frctl->new_col);
			j++;
		}
		i++;
	}
}

void	get_c_burningship(t_data *frctl, int x, int y)
{
	frctl->c_a = (x - ((double)frctl->w / 2))
		/ ((double)frctl->w / 4) * frctl->zoom + frctl->x_offset;
	frctl->c_b = (y - ((double)frctl->h / 2))
		/ ((double)frctl->h / 4) * frctl->zoom + frctl->y_offset;
}

void	get_iter_burningship(t_data *frctl)
{
	double	x;
	double	y;
	double	tmp;

	frctl->iter = 0;
	frctl->max = 100;
	x = 0;
	y = 0;
	while (x * x + y * y <= 2 * 2 && frctl->iter < frctl->max)
	{
		tmp = (x * x) - (y * y) + frctl->c_a;
		y = (fabs(2 * x * y)) + frctl->c_b;
		x = tmp;
		frctl->iter++;
	}
}
