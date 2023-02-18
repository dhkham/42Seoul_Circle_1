/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:13:04 by dkham             #+#    #+#             */
/*   Updated: 2023/02/18 17:09:13 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *frctl, int x, int y, int color)
{
	char	*dst;

	dst = frctl->addr + (y * frctl->line_length + x * (frctl->bpp / 8));
	*(unsigned int *) dst = color;
}
