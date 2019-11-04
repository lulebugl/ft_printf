# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 17:50:44 by lulebugl          #+#    #+#              #
#    Updated: 2019/11/04 14:27:57 by lulebugl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c				\
		parse_prespecifiers.c	\
		parse_specifier.c 		\
		int_conv.c				\
		uint_handlers.c			\
		str_char_handlers.c		\
		special_handlers.c		\
		printf_gen_utils.c		\
		printf_int_utils.c		\

OBJ = $(SRCS:.c=.o)

HEADERS = ft_printf.h libft/libft.h

all: $(NAME)
	@echo "\033[0;32mlibftprintf.a compiled successfully\033[0m"

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

libft/libft.a:
	@make -C ./libft

$(NAME): libft/libft.a $(OBJ)
	@ar rcs $(NAME) $(OBJ) libft/*.o

clean:
	@/bin/rm -f $(OBJ)
	@make -C ./libft clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
