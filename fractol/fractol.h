/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:32:54 by dkham             #+#    #+#             */
/*   Updated: 2023/02/13 22:19:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "stdio.h"
#include "stdlib.h"
#include "./mlx/mlx.h"
#include "./libft/libft.h"

#define X_EVENT_KEY_PRESS 2     // mlx_hook 함수의 두 번째 인자인 x_event에 들어가는 값
#define X_EVENT_KEY_RELEASE 3
#define X_EVENT_KEY_EXIT 17
#define KEY_UP 126  // '↑' '↓' '←' '→' 키보드 코드
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53  
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DOWN 5 

typedef struct s_data
{
	int width;
	int height;
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *addr;
	int bpp;
	int line_length;
	int endian;
	char *name;
	int base_col;
	int new_col;
	int c_a;
	int c_b;
	int iter;
	int max;
	// int move_x;
	// int move_y;
	
	int jx;
	int jy;
	
	double zoom;
}				t_data;

void	set_frctl(t_data *frctl, int argc, char **argv);
void	mandelbrot(t_data *frctl);
void	get_c(t_data *frctl, int x, int y); 
void	init_mandelbrot(t_data *frctl);
void	my_mlx_pixel_put(t_data *frctl, int x, int y, int color);

void	key(int keycode, t_data *frctl);
void	mouse(int mouse_code, t_data *frctl);
int		quit(void);

void	init_julia(t_data *frctl, double x, double y);
void	init(t_data *frctl, double *k, int i, int j);
void	julia(t_data *frctl);



#endif


	