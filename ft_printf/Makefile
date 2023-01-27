NAME	= libftprintf.a

CC		= cc
CFLAG	= -Wall -Wextra -Werror

RM		= rm -f
AR		= ar
ARFLAGS = crs

LIB_DIR = ./libft

SRCS	= ft_printf.c		\
		  print_cspercent.c	\
		  print_idu.c		\
		  print_hex.c		\

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	make -C $(LIB_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re : fclean all

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $(ARFLAGS) $@ $^

 .PHONY : all clean fclean re