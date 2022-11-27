# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmardin <wmardin@student.42wolfsburg.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 13:39:51 by wmardin           #+#    #+#              #
#    Updated: 2022/11/17 10:35:07 by wmardin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
AR = ar rcs

COLOR = \033[94m
COLOR_END = \033[0m

NAME = libft.a

PATH_ft_is = src/ft_is
PATH_ft_list = src/ft_list
PATH_ft_mem = src/ft_mem
PATH_ft_put = src/ft_put
PATH_ft_string = src/ft_string
PATH_ft_gnl = src/ft_gnl
PATH_ft_printf = src/ft_printf
PATH_mulain = src/mulain

SRC =	$(addprefix $(PATH_ft_is)/, ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c)\
		$(addprefix $(PATH_ft_list)/, ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c)\
		$(addprefix $(PATH_ft_mem)/, ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c)\
		$(addprefix $(PATH_ft_put)/, ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c)\
		$(addprefix $(PATH_ft_string)/, ft_atoi.c ft_itoa.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c)\
		$(addprefix $(PATH_ft_gnl)/, get_next_line.c get_next_line_utils.c)\
		$(addprefix $(PATH_ft_printf)/, ft_checkformat.c ft_printchar.c ft_printdecimal.c ft_printf.c ft_printhex_lower.c ft_printhex_upper.c ft_printint.c ft_printpointer.c ft_printstring.c ft_printunsignedint.c)\
		$(addprefix $(PATH_mulain)/, is_intsize.c is_numberformat.c printlist.c strlen_mod.c)

OBJ_DIR = obj
OBJ	= $(addprefix $(OBJ_DIR)/,$(SRC:src/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(COLOR)$(NAME) created.$(COLOR_END)"

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p obj/ft_is obj/ft_list obj/ft_mem obj/ft_put obj/ft_string obj/ft_gnl obj/ft_printf obj/mulain
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@rm -rf obj
	@echo "$(COLOR)clean performed.$(COLOR_END)"

fclean: clean
	@$(RM) $(NAME) a.out
	@echo "$(COLOR)fclean performed.$(COLOR_END)"

re: fclean all

git:
	git add .
	git commit -m "auto add & push"
	git push
	@echo "$(COLOR)git auto add & push performed.$(COLOR_END)"

.SILENT: $(OBJ)