NAME = minishell

SRC =	minishell.c
OBJ =	$(SRC:.c=.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

OBJ_F = Objects
LIBFT =	./Libft/libft.a

PINK	:= \033[0;35m
PURPLE	:= \033[0;34m
RESET	:= \033[0m

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(PINK)•$(RESET)\c"
# @MV $(OBJ) $(OBJ_F)/

$(NAME): $(OBJ) $(SRC)
	@mkdir $(OBJ_F)
	@$(MAKE) -C Libft
	@$(CC) $(LIBFT) $(OBJ) -o $(NAME) 
	@mv $(OBJ) $(OBJ_F)
	@echo "\n$(PINK)✨Minishell successfully compiled!✨$(RESET)"
#	@bash art.sh

clean:
	@$(MAKE) fclean -C Libft
	@$(RM) $(OBJ) $(OBJ_F)
	@echo "$(PURPLE)✨Minishell successfully cleaned!✨$(RESET)"

fclean: clean
	@$(RM) $(NAME)

re : fclean all
 
