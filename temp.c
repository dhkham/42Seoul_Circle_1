NAME 		= push_swap.a

CC 			= cc
# CFLAGS 		= -Wall -Wextra -Werror
AR          = ar -rcs
RM          = rm -f
LIBS		= libft/libft.a
SRCS		= push_swap.c push_swap_utils.c linked_list.c linked_list2.c \
			division_num.c push_swap_pasing.c push_swap_utils2.c \
			command/command_base.c command/command.c command/command2.c \
			command/command3.c sort_dir_check.c
SRCS_BONUS  =

OBJS        = $(SRCS:.c=.o) $(LIBS)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $@ $^

$(LIBS) :
	make -C libft all

bonus:
	@make WITH_BONUS=1 all

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:      
	$(RM) $(OBJS) $(OBJS_BONUS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)

re: 
	make fclean
	make all

.PHONY: all clean fclean re bonus