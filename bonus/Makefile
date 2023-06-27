NAME			=		philo_bonus

HEADER_PATH		=		includes_bonus

SOURCES_PATH	=		sources_bonus

OBJECTS_PATH	=		objects_bonus

SOURCES			=		philo_bonus.c

OBJECT			=		$(addprefix $(OBJECTS_PATH)/,	$(SOURCES:.c=.o))

CC				=		cc

C_FLAGS			=		-Wall -Wextra -Werror -g3 -I$(HEADER_PATH)

all:					$(NAME)

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