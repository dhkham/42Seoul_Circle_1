/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:13:39 by dkham             #+#    #+#             */
/*   Updated: 2023/02/11 20:16:21 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	key(int keycode, t_data *frctl) //int key...
{
	//mlx_clear_window(frctl->mlx_ptr, frctl->win_ptr);
	if (keycode == 53)
	{
		mlx_destroy_window(frctl->mlx_ptr, frctl->win_ptr);
		exit(0); // 필요?
	}
	else if (keycode == 18)
		frctl->base_col = 0x8033B5E5;
	else if (keycode == 19)
		frctl->base_col = 0x80FF0099;
	else if (keycode == 20)
		frctl->base_col = 0x80FF1493;
	// if (keycode == 2 || keycode == 124)
	// 	frctl->move_x += 0.1;
	// if (keycode == 0 || keycode == 123)
	// 	frctl->move_x += -0.1;
	// if (keycode == 13 || keycode == 126)
	// 	frctl->move_y += -0.1;
	// if (keycode == 1 || keycode == 125)
	// 	frctl->move_y += 0.1;
	if (ft_strncmp(frctl->name, 'mandelbrot', 10) == 0)
		mandelbrot(frctl);
	else if (ft_strncmp(frctl->name, 'julia', 5) == 0)
		julia(frctl);
	mlx_put_image_to_window(frctl->mlx_ptr, frctl->win_ptr, \
	frctl->img_ptr, 0, 0);
}

void	mouse(int mouse_code, t_data *frctl) //int mouse...
{
	// (void)x;
	// (void)y;
	//mlx_clear_window(frctl->mlx_ptr, frctl->win_ptr); // clear_window 있어야 하는지 체크
	// frctl->move_x = 0;
	// frctl->move_y = 0;
	if (mouse_code == 5)
		frctl->zoom *= 1.05;
	else if (mouse_code == 4)
		frctl->zoom /= 1.05;
	if (ft_strncmp(frctl->name, 'mandelbrot', 10) == 0)
		mandelbrot(frctl);
	else if (ft_strncmp(frctl->name, 'julia', 5) == 0)
		julia(frctl);
	mlx_put_image_to_window(frctl->mlx_ptr, frctl->win_ptr, \
	frctl->img_ptr, 0, 0);
}

int	quit(void)
{
	exit(0); // 바로 exit(0) mlx_hook에 써도 되는지 체크
}
