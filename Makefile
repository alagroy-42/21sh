# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alagroy- <alagroy-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 09:44:51 by alagroy-          #+#    #+#              #
#    Updated: 2019/05/23 17:39:04 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

SRCS_NAME = main.c readline.c terminit.c move.c tools.c

SRCS = $(addprefix srcs/, $(SRCS_NAME))

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES)

DFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address -I $(INCLUDES)

INCLUDES = includes

OBJ = $(SRCS:.c=.o)

%.o: %.c
	@printf "\033[0;32m[21sh] Compilation [.o]\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[21sh] Compilation [.o]\r"

all: $(NAME)

debug:
	$(CC) $(DFLAGS) -ltermcap libft/*.c $(SRCS) -o $(NAME)

$(NAME): $(OBJ)
	@printf "\033[0;32m[21sh] Compilation [OK]\n"
	@make -C libft
	@printf "\033[0;32m[21sh] Linking [.o]\r"
	@$(CC) $(CFLAGS) -L libft -lft -ltermcap $(OBJ) -o $(NAME)
	@printf "\033[0;32m[21sh] Linking [OK]\n"

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@printf "\033[0;31m[21sh] Clean [OK]\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f libft.a
	@printf "\033[0;31m[21sh] Fclean [OK]\n"

re: fclean all

.PHONY: fclean clean all re debug
