NAME = minishell

CC = gcc
CFLAGS =
EFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lreadline
RL_FLAG =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
RL_FLAG_O =  -I $(HOME)/goinfre/.brew/opt/readline/include/
RM = rm -rf

PINK	:= \033[0;35m
PURPLE	:= \033[0;34m
BLUE	= \033[94m
RESET	:= \033[0m

SRC = 	src/minishell.c\
		$(addprefix src/exec/,\
		input_config.c\
		better_libft.c\
		minihell.c\
		builtin_config.c\
		output_config.c\
		find_path.c)\
		$(addprefix src/parsing/,\
		00_parsing.c\
		01_preproc_syntax.c\
		02_lexer.c\
		03_expand_var.c\
		04_remove_quotes.c\
		05_postproc_syntax.c\
		06_parser.c\
		07_check_builtin.c\
		07_util_is.c\
		07_util_general.c\
		08_helper_print.c\
		09_msg.c\
		10_shutdown1.c\
		10_shutdown2.c)\
		$(addprefix src/signals/,\
		signals.c\
		og_signals.c)\
		$(addprefix src/builtins/,\
		cd.c\
		echo.c\
		env.c\
		exit.c\
		export_init.c\
		export_ordering.c\
		export.c\
		pwd.c\
		unset.c)
OBJ	=	$(addprefix obj/, $(SRC:src/%.c=%.o))
LIBFT =	src/libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LIBFLAGS) $(RL_FLAG)
	@bash src/pixel.sh
	@echo "$(PINK)✨Minishell successfully compiled!✨$(RESET)\n"
#@./minishell

$(LIBFT):
	@make --no-print-directory -C src/libft

obj/%.o: src/%.c
	@mkdir -p obj
	@mkdir -p obj/parsing obj/exec obj/signals obj/builtins
	$(CC) $(EFLAGS) -c $<  $(RL_FLAG_O) -o $@

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
	@echo "$(BLUE)git auto add & push with message performed.$(RESET)"

.SILENT: $(OBJ)