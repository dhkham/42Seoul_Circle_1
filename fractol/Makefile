# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkham <dkham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 20:23:05 by dkham             #+#    #+#              #
#    Updated: 2023/02/11 20:29:15 by dkham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
CC		=	cc
SUBDIR	=	libft
SUBLIB	=	ft
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm	-rf

SRCS 	=	fractol.c events.c \
			my_mlx_pixel_put.c \
			./plot_fractal/mandelbrot.c \
			./plot_fractal/julia.c \
			
LIB_DIR = ./libft


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(SRCS)
	$(MAKE) all -C mlx
	$(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make -C $(LIB_DIR) clean
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	make -C $(LIB_DIR) fclean
	$(MAKE) fclean -C mlx

re: fclean $(NAME)

.PHONY = all clean fclean re
