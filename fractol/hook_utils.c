/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:13:39 by dkham             #+#    #+#             */
/*   Updated: 2023/02/18 17:32:12 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key(int keycode, t_data *frctl)
{
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
	offset(frctl, keycode);
	init_fractol(frctl);
	mlx_put_image_to_window(frctl->mlx_ptr, frctl->win_ptr, \
	frctl->img_ptr, 0, 0);
	return (0);
}

void	offset(t_data *frctl, int keycode)
{
	if (keycode == KEY_UP)
		frctl->y_offset += 0.02;
	else if (keycode == KEY_DOWN)
		frctl->y_offset -= 0.02;
	else if (keycode == KEY_LEFT)
		frctl->x_offset -= 0.02;
	else if (keycode == KEY_RIGHT)
		frctl->x_offset += 0.02;
}

int	mouse(int mouse_code, int x, int y, t_data *frctl)
{
	(void)x;
	(void)y;
	mlx_clear_window(frctl->mlx_ptr, frctl->win_ptr);
	if (mouse_code == MOUSE_SCROLL_DOWN)
		frctl->zoom *= 1.05;
	else if (mouse_code == MOUSE_SCROLL_UP)
		frctl->zoom /= 1.05;
	init_fractol(frctl);
	mlx_put_image_to_window(frctl->mlx_ptr, frctl->win_ptr, \
	frctl->img_ptr, 0, 0);
	return (0);
}

void	init_fractol(t_data *frctl)
{
	char	*name1;
	char	*name2;
	char	*name3;

	name1 = "mandelbrot";
	name2 = "julia";
	name3 = "burningship";
	if (ft_strncmp(frctl->name, name1, 10) == 0)
		mandelbrot(frctl);
	else if (ft_strncmp(frctl->name, name2, 5) == 0)
		julia(frctl);
	else if (ft_strncmp(frctl->name, name3, 11) == 0)
		burningship(frctl);
}

int	quit(void)
{
	exit(0);
	return (0);
}
