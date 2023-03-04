NAME	= push_swap.a

CC		= cc
CFLAG	= -Wall -Wextra -Werror

RM		= rm -f
AR		= ar
ARFLAGS = crs

LIB_DIR = ./libft

SRCS	= main.c				\
		  push_swap.c			\
		  dequefunctions.c		\
		  command.c				\
		  checker.c				\

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	cp $(LIB_DIR)/libft.a $@
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	make -C $(LIB_DIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re : fclean all

 .PHONY : all clean fclean re
