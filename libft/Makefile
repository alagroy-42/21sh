# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 15:29:46 by alagroy-          #+#    #+#              #
#    Updated: 2019/09/19 15:00:49 by alagroy-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c \
	   ft_strlcat.c ft_strlen.c ft_strncmp.c ft_strncpy.c ft_strnstr.c \
	   ft_strrchr.c ft_strstr.c ft_strncat.c ft_atoi.c ft_isalpha.c \
	   ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c \
	   ft_tolower.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	   ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	   ft_strsub.c ft_strstrjoin.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	   ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memset.c ft_bzero.c \
	   ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	   ft_memalloc.c ft_memdel.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	   ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strrev.c ft_strlowcase.c \
	   ft_strupcase.c ft_strndup.c ft_lstsize.c ft_lstend.c ft_lstmid.c \
	   get_next_line.c aux.c edit_string.c fill_content.c flags.c ft_printf.c \
	   itoa.c precision_min_size.c tools.c ft_free_2da.c ft_print_2da.c \
	   ft_str2ddel.c ft_strreplace.c ft_print_strlist.c ft_expend_2dstr.c \
	   ft_2dstrlen.c ft_2dstrjoin.c ft_strichr.c ft_strirchr.c gnl_nl.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@printf "\033[0;32m[Libft] Compilation [o.]\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[0;32m[Libft] Compilation [o.]\r"

$(NAME): $(OBJ)
	@printf "[Libft] Compilation [OK]\n"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "[Libft] Libft.a [OK]\n"

clean: 
	@rm -f $(OBJ)
	@printf "\033[0;31m[Libft] Deleted *.o\n"
	
fclean: clean
	@rm -f $(NAME)
	@printf "\033[0;31D[Libft] Deleted libft.a\n"

re: clean all

.PHONY: fclean all re clean
