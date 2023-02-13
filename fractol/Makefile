# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkham <dkham@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 20:23:05 by dkham             #+#    #+#              #
#    Updated: 2023/02/13 22:13:27 by dkham            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
CC		=	cc

SUBDIR	=	libft
SUBLIB	=	ft

CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm	-f

SRCS 	=	fractol.c \
			events.c \
			my_mlx_pixel_put.c \
			ft_strncmp.c \
			./plot_fractol/mandelbrot.c \
			./plot_fractol/julia.c \

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(SRCS)
	$(MAKE) all -C mlx
	$(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C mlx

re: fclean $(NAME)

.PHONY = all clean fclean re