# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hturkatr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 13:28:22 by hturkatr          #+#    #+#              #
#    Updated: 2019/10/03 13:33:36 by hturkatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_atoi.c ft_bzero.c ft_countletters.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lst_add_tail.c ft_lst_elem_cpy.c ft_lstadd.c ft_lstcpy.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c ft_putendl.c ft_puterr.c ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstdel_elem.c ft_lstdelete.c ft_cheer_me_up.c ft_realloc.c ft_make_t_map.c ft_destroy_t_map.c ft_memdup.c ft_calloc.c
#
#SRC_OBJ = $(subst .c,.o,$(SRC))
#
#COMPILE = gcc -Wall -Wextra -Werror -c
#
#all:$(NAME)
#
#$(NAME): $(SRC_OBJ)
#	@ar rc $(NAME) $(SRC_OBJ)
#	@ranlib $(NAME)
#
#clean:
#	@/bin/rm -f $(SRC_OBJ)
#	@/bin/rm -f *~
#
#fclean: clean
#	@/bin/rm -f $(NAME)
#
#re: fclean all
#
#.c.o:
#	gcc -Wall -Wextra -Werror -c $< -o $@
#
#.PHONY: clean fclean all re update

INCLUDE = -I libft.h
OBJ = $(subst .c,.o,$(SRCS))
all: $(NAME)
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
%.o: %.c
	@gcc -Wall -Wextra -Werror $(INCLUDE) $< -c -o $@
clean:
	@/bin/rm -f $(OBJ)
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re