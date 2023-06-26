NAME			=		philo

HEADER_PATH		=		includes

SOURCES_PATH	=		sources

OBJECTS_PATH	=		objects

SOURCES			=		data_init.c \
						dinner_utils.c \
						dinner.c \
						monitor.c \
						philo_utils.c \
						philo.c \
						threads.c \
						time_utils.c

OBJECT			=		$(addprefix $(OBJECTS_PATH)/,	$(SOURCES:.c=.o))

CC				=		cc

C_FLAGS			=		-pthread -Wall -Wextra -Werror -g3 -I$(HEADER_PATH)

all: $(NAME)

$(NAME):				$(OBJECTS_PATH) $(OBJECT)
						$(CC) $(C_FLAGS) $(OBJECT) -o $@

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/philo.h
						@$(CC) $(C_FLAGS) -c $< -o $@

clean:
						rm -rf $(OBJECTS_PATH)

fclean:					clean
						rm -f $(NAME)

re:						fclean all

.PHONY:					all clean fclean re