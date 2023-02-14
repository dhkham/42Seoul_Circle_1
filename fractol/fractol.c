/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:25:20 by dkham             #+#    #+#             */
/*   Updated: 2023/02/14 21:28:46 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_data	frctl;

	if (argc < 1 || argc > 3)
		printf("ERROR: Invalid number of arguments");
	else
	{
		set_frctl(&frctl, argc, argv);// my_mlx_pixel_put 까지 실행
		mlx_put_image_to_window(frctl.mlx_ptr, frctl.win_ptr, \
		frctl.img_ptr, 0, 0);//생성한 이미지를 윈도우에 띄움 (my_mlx_pixel_put 이후)
		// mlx_hook(frctl.win_ptr, X_EVENT_KEY_PRESS, 0, key, &frctl);//키보드 입력
		// mlx_hook(frctl.win_ptr, MOUSE_SCROLL_UP, 0, mouse, &frctl);//마우스 입력
		//mlx_hook(frctl.win_ptr, X_EVENT_KEY_EXIT, 0, exit, 0); //x버튼 입력
		//mlx_hook(frctl.win_ptr, X_EVENT_KEY_EXIT, 1L << 17, ft_exit, 0); //1L << 17 필요?
		mlx_loop(frctl.mlx_ptr);
	}
}

void	set_frctl(t_data *frctl, int argc, char **argv)
{
	frctl->width = 800;
	frctl->height = 800;
	frctl->mlx_ptr = mlx_init();
	frctl->win_ptr = mlx_new_window(frctl->mlx_ptr, frctl->width, \
	frctl->height, "fract-ol");
	frctl->img_ptr = mlx_new_image(frctl->mlx_ptr, frctl->width, \
	frctl->height);//이미지 객체 생성(메모리에 새 이미지 생성. 지정한 가로세로 크기의 그림을 그려둠)
	frctl->addr = mlx_get_data_addr(frctl->img_ptr, &frctl->bpp, \
	&frctl->line_length, &frctl->endian);//생성된 이미지에 대한 정보 리턴
	frctl->base_col = 0x0000FF00;// 기본
	frctl->new_col = 0;
	frctl->zoom = 1;// 맞는지 확인!!
	if (argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0)
	{
		frctl->name = "mandelbrot";
		mandelbrot(frctl);
	}
	else if (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0) // 제대로 두 값 받았는지 체크 더 해야 (소수점 등등 확인)
	{
		frctl->name = "julia";
		julia(frctl);
	}
	else
		printf("ERROR: Invalid argument");
}
