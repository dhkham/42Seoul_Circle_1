NAME 		= libftprintf.a
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
AR          = ar -rcs
RM          = rm -f
SRCS		= ft_printf.c print.c ft_atoi.c ft_isdigit.c ft_strchr.c ft_strlen.c
OBJS        = $(SRCS:.c=.o)
OBJECTS 	= $(OBJS)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:      
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: 
	make fclean
	make all

bonus: all

.PHONY: all clean fclean re bonus