# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 09:44:51 by alagroy-          #+#    #+#              #
#    Updated: 2019/08/12 17:00:48 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

SRCS_NAME = altkey.c ast_generate.c ast_set.c ast_tools.c builtin.c builtin_cd.c ctrl_key.c debugging.c \
			env.c exec.c history.c lexer.c machine_func.c machine_specialchar_func.c \
			main.c move.c parser.c readline.c readline_tools.c terminit.c \
			analize.c visumod.c visumove.c readline_aux.c visu_op.c redir.c \
			input.c output.c signal.c autocomplete.c lite_parser.c \
			autocmplt_tools.c expansions.c advanced_cmplt.c special_param.c \
			sighandler.c

SRCS = $(addprefix srcs/, $(SRCS_NAME))

CFLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES)

DFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -I $(INCLUDES)

INCLUDES = includes

OBJ_FILE = $(SRCS_NAME:.c=.o)

OBJ = $(addprefix .obj/, $(OBJ_FILE))

.obj/%.o: srcs/%.c
	@mkdir .obj 2>/dev/null || true
	@printf "\033[0;32m[21sh] Compilation [.o]\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[21sh] Compilation [.o]\r"

all: $(NAME)

debug:
	$(CC) $(DFLAGS) libft/*.c $(SRCS) -ltermcap -o $(NAME)

$(NAME): $(OBJ)
	@printf "\033[0;32m[21sh] Compilation [OK]\n"
	@make -C libft
	@printf "\033[0;32m[21sh] Linking [.o]\r"
	@$(CC) $(CFLAGS) $(OBJ) -L libft -lft -ltermcap -o $(NAME)
	@printf "\033[0;32m[21sh] Linking [OK]\n"

clean:
	@make -C libft clean
	@rm -Rf .obj
	@printf "\033[0;31m[21sh] Clean [OK]\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f libft.a
	@printf "\033[0;31m[21sh] Fclean [OK]\n"

re: fclean all

.PHONY: fclean clean all re debug
