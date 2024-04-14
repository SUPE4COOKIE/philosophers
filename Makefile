CC = cc
CFLAGS = -MMD -MP -Wall -Wextra -Werror -pthread -g3
NAME = philo

SRC_PATH = src
SRC_FILES = args_parser.c ft_atoi.c philosophers.c utils.c actions.c
HEADER_PATH = includes
HEADER_FILES = philosophers.h errors.h actions.h
HEADERS = $(addprefix $(HEADER_PATH)/, $(HEADER_FILES))
SRCS = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
OBJDEPS = $(addprefix $(OBJ_PATH)/, $(OBJ:.o=.d))

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile $(HEADERS) | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

-include $(OBJDEPS)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re