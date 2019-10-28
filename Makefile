# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 17:50:44 by lulebugl          #+#    #+#              #
#    Updated: 2019/10/26 05:20:37 by lulebugl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftprintf.a

INC = includes/ft_printf.h

SRCS	= ft_strlen.c 			\
			ft_atoi.c			\
			ft_isdigit.c		\
			ft_putchar.c		\
			ft_itoa.c			\
			ft_parsing.c		\
			ft_print_char.c		\
			ft_printf.c			\
			ft_printing.c		\
			ft_strchr.c			\
			ft_putstr.c			\
			ft_print_str.c		\
			ft_putnbr.c			\
			ft_print_nbr.c		\
			ft_print_percent.c	\
			ft_utoa.c			\
			ft_print_unsign.c	\
			ft_hextoa.c			\
			ft_print_hex.c		\
			ft_hexcaptoa.c		\
			ft_print_pointer.c	\
			
SRCSFD = srcs/

OBJSFD = objs/

OBJS	= $(addprefix $(OBJSFD), $(SRCS:.c=.o))

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(OBJSFD) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJSFD) :
	mkdir $@

$(OBJSFD)%.o: $(SRCSFD)%.c
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

all : $(NAME)

clean :	
	rm -rf $(OBJSFD)
	
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
