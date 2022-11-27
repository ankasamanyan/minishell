NAME = minishell

CC = gcc
CFLAGS = -g
EFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LIBFLAGS = -lreadline
RM = rm -rf

PINK	:= \033[0;35m
PURPLE	:= \033[0;34m
BLUE	= \033[94m
RESET	:= \033[0m

SRC = 	src/minishell.c\
		src/exec/file_config.c\
		src/exec/better_libft.c\
		src/exec/minihell.c\
		$(addprefix src/parsing/,\
		0_parsing.c\
		1_syntax.c\
		2_expand_envvar.c\
		2_make_tokens.c\
		3_make_commands.c\
		6_util_get.c\
		6_util_is.c\
		7_helper_print.c\
		8_exits+broadcast.c)
OBJ	=	$(addprefix obj/, $(SRC:src/%.c=%.o))
LIBFT =	src/libft/libft.a
#$(addprefix obj/,$(notdir $(SRC:src/%.c=%.o)))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) $(LIBFLAGS) -o $(NAME) $(LIBFT)
	@bash src/pixel.sh
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

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(BLUE)git auto add & push performed.$(RESET)"

mgit:
	git add .
	@read -p "Enter the commit message: " halp; \
	git commit -m "$$halp"
	git push
	@echo "$(PURPLE)✨Everything added, commited and pushed✨$(RESET)"

.SILENT: $(OBJ)