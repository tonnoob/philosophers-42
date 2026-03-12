NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

DEBUG = -g

SRC_DIR = src
OBJ_DIR = obj

SRC = main.c init.c parser.c actions.c \
	  actions_utils.c monitoring.c simulation.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC))

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@echo "✅ Executável philo criado"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Objetos removidos."

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  Tudo limpo!"

re: fclean all

valgrind: debug
	@echo "🔍 Verificando vazamentos"
	valgrind --leak-check=full \
			 --show-leak-kinds=all \
			 --track-origins=yes \
			 --track-fds=yes \
			 ./$(NAME) $(ARGS)
	
debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re