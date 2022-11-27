CC = gcc
CFLAGS = -g
ERRORFLAGS = -Wall -Wextra -Werror
LIBRARYFLAGS = -lreadline
DEFINE =

NAME =	parsing
SRC =	0_parsing.c\
		6_utils_is.c\
		8_exits.c

LIBFT = ../libft/libft.a

COLOR = \033[94m
COLOR_END = \033[0m

%.o: %.c

$(NAME): $(LIBFT)
	@$(CC) $(CFLAGS) $(ERRORFLAGS) $(SRC) $(LIBFT) $(DEFINE) $(LIBRARYFLAGS) -o $(NAME)
	@echo "$(COLOR)$(NAME) created."

$(LIBFT):
	@make --no-print-directory -C ../libft

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "$(COLOR)clean performed."

fclean: clean
	@$(RM) $(NAME)
	@rm -rf obj
	@echo "$(COLOR)fclean performed."

re: fclean all

noflag:
	@$(CC) $(CFLAGS) $(SRC) $(DEFINE) -o $(NAME)
	@echo "$(COLOR)$(NAME) created w/o error flags."

test:
	@$(CC) $(CFLAGS) $(SRC) -o test

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(COLOR)git auto add & push performed."