/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkham <dkham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:13:04 by dkham             #+#    #+#             */
/*   Updated: 2023/02/11 16:41:54 by dkham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *frctl, int x, int y, int color)
{
// my_mlx_pixel_put 함수는 mlx_pixel_put 함수를 대체하는 함수이다.
// mlx_pixel_put 함수는 mlx 라이브러리를 사용하여 화면에 픽셀을 그리는 함수이다.
	char	*dst;

	dst = frctl->addr + (y * frctl->line_length + x * (frctl->bpp / 8));
	*(unsigned int *) dst = color;
}
//addr: 이미지가 저장된 메모리 시작 지점의 주소
//y좌표에 line_length를 곱해서 원하는 y좌표가 있는 주소까지 점프
//이제 x좌표 만큼만 이동하면 된다. x에 곱해주는 (data->bits_per_pixel / 8)은 픽셀에 들어있는 비트수를 8로 나눈 값을 곱하게 된다!
//우리는 픽셀당 32개의 bit가 들어있기 때문에 x×4가 되는 것이다.(주소는 byte단위로 이동하기 때문에!!)
//그 위치에 우리가 매개변수로 넘겨준 color값을 넣어주면 끝이다! 
//나중에 프로그램이 해당 메모리를 읽으면서 좌표마다 32비트의 color값을 읽게 되고 
//우리가 띄운 디스플레이 상의 윈도우 x, y좌표에 해당하는 color를 표현하게 된다!

// The function starts by calculating a pointer "dst" to the 
// memory location of the pixel to be drawn. 
// This is done by adding the offset of the desired y-coordinate to the start 
// address of the display buffer (frctl->addr), and then adding the offset of the 
// x-coordinate multiplied by the number of bytes per pixel. 
// The number of bytes per pixel is calculated by dividing the bits per pixel 
// value by 8.
// Finally, the color value is written to the memory location pointed to by "dst", 
// which will draw the pixel on the display or image buffer. 
// The cast to "unsigned int " is used to treat the memory location as a 
// pointer to an unsigned integer, which is the format in which the color value 
// is stored. The dereference operator "" is used to write the value of "color" 