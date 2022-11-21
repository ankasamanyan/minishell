NAME =	minishell

SRC =	src/minishell.c src/better_libft.c src/checks.c
OBJ =	$(SRC:.c=.o)

CC =	gcc
FLAGS = -Wall -Wextra -Werror 
OTHER_FLAGS = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

RM =	rm -rf

OBJ_F = obj
READ =	read -r 

LIBFT =	./Libft/libft.a

PINK	:= \033[0;35m
PURPLE	:= \033[0;34m
RESET	:= \033[0m

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS)-c $< -o $@
	@echo "$(PINK)•$(RESET)\c"

$(NAME): $(OBJ) $(SRC)
	@$(MAKE) -C Libft
	@$(CC) $(LIBFT) $(OBJ) $(OTHER_FLAGS) -o $(NAME) 
	@mv $(OBJ) $(OBJ_F)/
	@echo "\n$(PINK)✨Minishell successfully compiled!✨$(RESET)"

clean:
	@$(MAKE) fclean -C Libft
	@$(RM) $(OBJ_F)/*
	@echo "$(PURPLE)✨Minishell successfully cleaned!✨$(RESET)"

fclean: clean
	@$(RM) $(NAME)

git:
	git add .
	@read -p "Enter the commit message: " halp; \
	git commit -m "$$halp"
	git push
	@echo "$(PURPLE)✨All added, commited and pushed!✨$(RESET)"
re : fclean all
