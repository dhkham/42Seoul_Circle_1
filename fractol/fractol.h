/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:32:54 by dkham             #+#    #+#             */
/*   Updated: 2023/02/15 21:52:27 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "stdio.h"
#include "stdlib.h"
#include "./mlx/mlx.h"
#include "./libft/libft.h"

#define X_EVENT_KEY_EXIT 17
#define KEY_ESC 53  
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
	int jc_a;
	int jc_b;
	double zoom;
}				t_data;

void	set_frctl(t_data *frctl, int argc, char **argv);

void	mandelbrot(t_data *frctl);
void	get_c(t_data *frctl, int x, int y); 
void	get_iter_mandelbrot(t_data *frctl);
void	my_mlx_pixel_put(t_data *frctl, int x, int y, int color);

int		key(int keycode, t_data *frctl);
int		mouse(int mouse_code, int x, int y, t_data *frctl);
int		quit(void);

void	get_iter_julia(t_data *frctl, double x, double y);
void	init(t_data *frctl, double *k, int i, int j);
void	julia(t_data *frctl);

double	ft_atof(char *str, t_data *frctl);
int		atof_split(char c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);

#endif


	