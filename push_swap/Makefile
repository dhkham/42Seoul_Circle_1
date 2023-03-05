NAME	= push_swap
CC		= cc
CFLAG	= -Wall -Wextra -Werror
RM		= rm -f
SRCS	= main.c								\
		  push_swap.c							\
		  dequefunctions.c						\
		  command.c								\

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : libs $(OBJS)
	$(CC) $(CFLAG) $(SRCS) -L./libft -lft -o $(NAME)

libs :
	make -C libft

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	make -C ./libft clean
	$(RM) $(OBJS)

fclean : clean
	make -C ./libft fclean
	$(RM) $(NAME)

re : fclean all

 .PHONY : all clean fclean re
