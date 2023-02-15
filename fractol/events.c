/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:13:39 by dkham             #+#    #+#             */
/*   Updated: 2023/02/15 21:07:11 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key(int keycode, t_data *frctl)
{
	char	*name1;
	char	*name2;

	name1 = "mandelbrot";
	name2 = "julia";
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(frctl->mlx_ptr, frctl->win_ptr);
		exit (0);
	}
	else if (keycode == 18)
		frctl->base_col = 0x8033B5E5;
	else if (keycode == 19)
		frctl->base_col = 0x80FF0099;
	else if (keycode == 20)
		frctl->base_col = 0x80FF1493;
	if (ft_strncmp(frctl->name, name1, 10) == 0)
		mandelbrot(frctl);
	else if (ft_strncmp(frctl->name, name2, 5) == 0)
		julia(frctl);
	mlx_put_image_to_window(frctl->mlx_ptr, frctl->win_ptr, \
	frctl->img_ptr, 0, 0);
	return (0);
}

int	mouse(int mouse_code, int x, int y, t_data *frctl)
{
	char	*name1;
	char	*name2;

	(void)x;
	(void)y;
	mlx_clear_window(frctl->mlx_ptr, frctl->win_ptr);
	name1 = "mandelbrot";
	name2 = "julia";
	if (mouse_code == MOUSE_SCROLL_DOWN)
		frctl->zoom *= 1.05;
	else if (mouse_code == MOUSE_SCROLL_UP)
		frctl->zoom /= 1.05;
	if (ft_strncmp(frctl->name, name1, 10) == 0)
		mandelbrot(frctl);
	else if (ft_strncmp(frctl->name, name2, 5) == 0)
		julia(frctl);
	mlx_put_image_to_window(frctl->mlx_ptr, frctl->win_ptr, \
	frctl->img_ptr, 0, 0);
	return (0);
}

int	quit(void)
{
	exit(0); // 바로 exit(0) mlx_hook에 써도 되는지 체크
	return (0);
}
