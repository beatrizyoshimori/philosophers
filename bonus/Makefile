NAME			=		philo_bonus

HEADER_PATH		=		includes_bonus

SOURCES_PATH	=		sources_bonus

OBJECTS_PATH	=		objects_bonus

SOURCES			=		data_init_bonus.c \
						dinner_bonus.c \
						philo_bonus.c \
						philo_utils_bonus.c \
						time_utils_bonus.c

OBJECT			=		$(addprefix $(OBJECTS_PATH)/,	$(SOURCES:.c=.o))

CC				=		cc

C_FLAGS			=		-pthread -Wall -Wextra -Werror -g3 -I$(HEADER_PATH)

all:					$(NAME)

bonus:					all

$(NAME):				$(OBJECTS_PATH) $(OBJECT)
						$(CC) $(C_FLAGS) $(OBJECT) -o $@

$(OBJECTS_PATH):
						@mkdir -p $(OBJECTS_PATH)

$(OBJECTS_PATH)/%.o:	$(SOURCES_PATH)/%.c $(HEADER_PATH)/philo_bonus.h
						@$(CC) $(C_FLAGS) -c $< -o $@

clean:
						rm -rf $(OBJECTS_PATH)

fclean:					clean
						rm -f $(NAME)

re:						fclean all

.PHONY:					all clean fclean re