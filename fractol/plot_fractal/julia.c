/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:25:32 by dkham             #+#    #+#             */
/*   Updated: 2023/02/16 17:56:53 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// julia 확인

void	julia(t_data *frctl)
{
	int	i;
	int	j;

	i = 0;
	while (i < frctl->w)
	{
		j = 0;
		while (j < frctl->h)
		{
			get_c(frctl, i, j);
			get_iter_julia(frctl);
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

// void	get_c(t_data *frctl, int x, int y)
// {
// 	frctl->c_a = (x - ((double)frctl->w / 2))
// 		/ ((double)frctl->w / 4) * frctl->zoom;
// 	frctl->c_b = -(y - ((double)frctl->h / 2))
// 		/ ((double)frctl->h / 4) * frctl->zoom;
// }

// void	get_iter_julia(t_data *frctl)
// {
// 	double	x;
// 	double	y;
// 	double	tmp;

// 	frctl->iter = 0;
// 	frctl->max = 100;
// 	x = 0;
// 	y = 0;
// 	while (x * x + y * y <= 2 * 2 && frctl->iter < frctl->max)
// 	{
// 		tmp = x;
// 		x = (x * x) - (y * y) + frctl->jc_a;
// 		y = (2 * tmp * y) + frctl->jc_b;
// 		frctl->iter++;
// 	}
// }
