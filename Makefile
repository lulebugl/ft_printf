# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 17:50:44 by lulebugl          #+#    #+#              #
#    Updated: 2019/11/24 20:01:57 by lulebugl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Werror -Wextra -I includes

SRCS = ft_printf.c				\
		parsing.c				\
		convtable.c				\
		int_handler.c			\
		uint_hex_p_handlers.c	\
		str_char_handlers.c		\
		percent_handlers.c		\
		printf_tools.c			\
		printf_int_utils.c		\

OBJ = $(SRCS:.c=.o)

all: $(NAME)
	@echo "\033[0;32mlibftprintf.a compiled successfully\033[0m"

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

libft/libft.a:
	@make -C ../libft

$(NAME): libft/libft.a $(OBJ)
	@ar rcs $(NAME) $(OBJ) ../libft/*.o

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
