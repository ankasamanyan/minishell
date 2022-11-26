
NAME = minishell

CC = gcc
CFLAGS = -g
EFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lreadline
RM = rm -rf

PINK	:= \033[0;35m
PURPLE	:= \033[0;34m
BLUE	= \033[94m
RESET	:= \033[0m

SRC = 	src/minishell.c\
		src/file_config.c\
		src/better_libft.c\
#		 $(addprefix src/parsing/,\
#		 0_parsing.c\
#		 1_syntax.c\
#		 2_expand_envvar.c\
#		 2_make_tokens.c\
#		 3_make_commands.c\
#		 6_util_get.c\
#		 6_util_is.c\
#		 7_helper_print.c\
#		 8_exits+broadcast.c)

OBJ	=	$(addprefix obj/, $(SRC:src/%.c=%.o))
LIBFT =	src/libft/libft.a
#$(addprefix obj/,$(notdir $(SRC:src/%.c=%.o)))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) $(LIBFLAGS) -o $(NAME) $(LIBFT)
	@bash pixel.sh
	@echo "$(PINK)✨Minishell successfully compiled!✨$(RESET)"
#	@bash src/art.sh

$(LIBFT):
	@make --no-print-directory -C src/libft

obj/%.o: src/%.c
	@mkdir -p obj
	@mkdir -p obj/parsing obj/exec
	$(CC) $(EFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) obj
	@echo "$(PINK)✨Minishell successfully cleaned!✨$(RESET)"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

# git:
# 	git add .
# 	git commit -m "auto add & push"
# 	git push
# 	@echo "$(BLUE)git auto add & push performed.$(RESET)"

git:
	git add .
	@read -p "Enter the commit message: " halp; \
	git commit -m "$$halp"
	git push
	@echo "$(BLUE)git auto add & push with message performed.$(RESET)"

.SILENT: $(OBJ)

# NAME =	minishell

# SRC =	src/minishell.c src/better_libft.c src/file_config.c
# OBJ =	$(SRC:.c=.o)

# CC =	gcc
# FLAGS = -Wall -Wextra -Werror 
# OTHER_FLAGS = -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

# RM =	rm -rf

# OBJ_F = obj
# READ =	read -r 

# LIBFT =	./Libft/libft.a

# PINK	:= \033[0;35m
# PURPLE	:= \033[0;34m
# RESET	:= \033[0m

# all: $(NAME)

# %.o: %.c
# 	@$(CC) $(FLAGS)-c $< -o $@
# 	@echo "$(PINK)•$(RESET)\c"

# $(NAME): $(OBJ) $(SRC)
# 	@$(MAKE) -C Libft
# 	@$(CC) $(LIBFT) $(OBJ) $(OTHER_FLAGS) -o $(NAME) 
# 	@mv $(OBJ) $(OBJ_F)/
# 	@echo "\n$(PINK)✨Minishell successfully compiled!✨$(RESET)"

# clean:
# 	@$(MAKE) fclean -C Libft
# 	@$(RM) $(OBJ_F)/*
# 	@echo "$(PURPLE)✨Minishell successfully cleaned!✨$(RESET)"

# fclean: clean
# 	@$(RM) $(NAME)

# git:
# 	git add .
# 	@read -p "Enter the commit message: " halp; \
# 	git commit -m "$$halp"
# 	git push
# 	@echo "$(PURPLE)✨All added, commited and pushed!✨$(RESET)"
# re : fclean all
