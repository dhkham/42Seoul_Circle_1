/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:25:20 by dkham             #+#    #+#             */
/*   Updated: 2023/02/16 18:01:28 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_data	frctl;
	
	if (argc != 2 && argc != 4)
		printf("!!!ERROR: invalid num of args!!!");
	else
	{
		set_frctl(&frctl, argc, argv); // my_mlx_pixel_put 까지 실행
		mlx_put_image_to_window(frctl.mlx_ptr, frctl.win_ptr, \
		frctl.img_ptr, 0, 0); // 생성한 이미지를 윈도우에 띄움 (my_mlx_pixel_put 이후)
		mlx_key_hook(frctl.win_ptr, &key, &frctl); // 키보드 입력
		mlx_mouse_hook(frctl.win_ptr, &mouse, &frctl); // 마우스 입력
	    mlx_hook(frctl.win_ptr, X_EVENT_KEY_EXIT, 0, quit, &frctl); // 창 닫기
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
	frctl->img_ptr = mlx_new_image(frctl->mlx_ptr, frctl->w, frctl->h);//이미지 객체 생성(메모리에 새 이미지 생성. 지정한 가로세로 크기의 그림을 그려둠)
	frctl->addr = mlx_get_data_addr(frctl->img_ptr, &frctl->bpp, \
	&frctl->line_length, &frctl->endian);//생성된 이미지에 대한 정보 리턴
	frctl->base_col = 0x00F8F8FF;
	frctl->new_col = 0;
	frctl->zoom = 1;
	if (argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0)
	{
		frctl->name = "mandelbrot";
		mandelbrot(frctl);
	}
	else if (argc == 4 && ft_strncmp(argv[1], "julia", 5) == 0) // 제대로 두 값 받았는지 체크 더 해야 (소수점 등등 확인)
	{
		frctl->name = "julia";
		frctl->jc_a = ft_atof(argv[1]);
		frctl->jc_b = ft_atof(argv[2]);
		julia(frctl);
	}
	else
		printf("!!!ERROR: invalid arg!!!");
}
