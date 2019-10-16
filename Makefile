# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 17:50:44 by lulebugl          #+#    #+#              #
#    Updated: 2019/10/16 18:36:24 by lulebugl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftprintf.a

INC = includes/ft_printf.h

SRCS	= ft_strlen.c 			\
			ft_atoi.c			\
			ft_itoa.c			\
			ft_printchar.c		\
			ft_putchar.c		\
			ft_printf.c			\
			ft_putstr.c			\
			ft_printstr.c		\
			ft_putnbr.c			\
			ft_printnbr.c		\
			ft_utoa.c			\
			ft_print_unsign.c	\
			ft_otoa.c			\
			ft_print_octal.c	\
			ft_hextoa.c			\
			ft_print_hex.c		\
			ft_hexcaptoa.c		\
			ft_print_hex_cap.c	\
			
SRCSFD = srcs/

OBJSFD = objs/

OBJS	= $(addprefix $(OBJSFD), $(SRCS:.c=.o))

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(OBJSFD) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

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
