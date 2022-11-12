NAME = minishell

SRC = minishell.c
OBJ = $(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

PINK	:= \033[0;35m
PURPLE	:= \033[0;34m
RESET	:= \033[0m

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(PINK)•$(RESET)\c"
	@echo "\n$(PINK)✨Minishell successfully compiled!✨$(RESET)"

$(NAME): $(OBJ) $(SRC)
		@$(CC) $(OBJ) -o $(NAME)
#		@bash art.sh

clean:
	@$(RM) $(OBJ)
	@echo "$(PINK)✨Minishell successfully cleaned!✨$(RESET)"

fclean: clean
	@$(RM) $(NAME)

re : fclean all
