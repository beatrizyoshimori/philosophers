NAME = philo
CFLAGS = -pthread -Wall -Wextra -Werror -g3

SRCS = philo.c \
	philo_utils.c \
	error.c \
	threads.c \
	dinner.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(OBJS) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re