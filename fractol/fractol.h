/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:32:54 by dkham             #+#    #+#             */
/*   Updated: 2023/02/16 22:12:12 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "stdio.h"
#include "stdlib.h"
#include "./mlx/mlx.h"
#include "./libft/libft.h"
#include "math.h"

#define X_EVENT_KEY_EXIT 17
#define KEY_ESC 53
#define KEY_UP 126
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_DOWN 125
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DOWN 5 

typedef struct s_data
{
	int w;
	int h;
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
	double c_a;
	double c_b;
	int iter;
	int max;
	double jc_a;
	double jc_b;
	double zoom;
	double x_offset;
	double y_offset;
}				t_data;

void	set_frctl(t_data *frctl, int argc, char **argv);
void	set_name(t_data *frctl, int argc, char **argv);

void	mandelbrot(t_data *frctl);
void	get_c_mandelbrot(t_data *frctl, int x, int y); 
void	get_iter_mandelbrot(t_data *frctl);
void	my_mlx_pixel_put(t_data *frctl, int x, int y, int color);

void	julia(t_data *frctl);
void	get_iter_julia(t_data *frctl, int i, int j);

void	burningship(t_data *frctl);
void	get_c_burningship(t_data *frctl, int x, int y);
void	get_iter_burningship(t_data *frctl);

int		key(int keycode, t_data *frctl);
void	offset(t_data *frctl, int keycode);
int		mouse(int mouse_code, int x, int y, t_data *frctl);
void	init_fractol(t_data *frctl);
int		quit(void);

double	ft_atod(const char *str);
void	handle_decimal(const char *str, int i, double *decimal);
int		judge_sign(const char *str, int i, int *sign);
int		skip_whitespace(const char *str, int i);


#endif


	