/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:25:20 by dkham             #+#    #+#             */
/*   Updated: 2023/02/18 17:32:51 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_data	frctl;

	if (argc != 2 && argc != 4)
		printf("ENTER: ./fractol [mandelbrot] or [julia -0.8 0.2]");
	else
	{
		set_frctl(&frctl, argc, argv);
		mlx_put_image_to_window(frctl.mlx_ptr, frctl.win_ptr, \
		frctl.img_ptr, 0, 0);
		mlx_key_hook(frctl.win_ptr, &key, &frctl);
		mlx_mouse_hook(frctl.win_ptr, &mouse, &frctl);
		mlx_hook(frctl.win_ptr, X_EVENT_KEY_EXIT, 0, quit, &frctl);
		mlx_loop(frctl.mlx_ptr);
	}
}

void	set_frctl(t_data *frctl, int argc, char **argv)
{
	frctl->w = 800;
	frctl->h = 800;
	frctl->mlx_ptr = mlx_init();
	frctl->win_ptr = mlx_new_window(frctl->mlx_ptr, frctl->w, \
	frctl->h, "fract-ol");
	frctl->img_ptr = mlx_new_image(frctl->mlx_ptr, frctl->w, frctl->h);
	frctl->addr = mlx_get_data_addr(frctl->img_ptr, &frctl->bpp, \
	&frctl->line_length, &frctl->endian);
	frctl->base_col = 0x00F8F8DD;
	frctl->new_col = 0;
	frctl->zoom = 1;
	set_name(frctl, argc, argv);
}

void	set_name(t_data *frctl, int argc, char **argv)
{
	if (argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0)
	{
		frctl->name = "mandelbrot";
		mandelbrot(frctl);
	}
	else if (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0)
	{
		frctl->name = "julia";
		frctl->jc_a = ft_atod(argv[2]);
		frctl->jc_b = ft_atod(argv[3]);
		julia(frctl);
	}
	else if (argc == 2 && ft_strncmp(argv[1], "burningship", 11) == 0)
	{
		frctl->name = "burningship";
		burningship(frctl);
	}
	else
	{
		printf("ENTER: ./fractol [mandelbrot] or [julia -0.8 0.2]");
		exit(1);
	}
}
