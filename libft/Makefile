# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lulebugl <lulebugl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 15:01:13 by lulebugl          #+#    #+#              #
#    Updated: 2019/10/22 18:28:06 by lulebugl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libft.a

SRCS	= ft_strlen.c 			\
			ft_atoi.c			\
			ft_strncmp.c		\
			ft_strlcat.c		\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isprint.c		\
			ft_isascii.c		\
			ft_isspace.c		\
			ft_memset.c			\
			ft_bzero.c			\
			ft_memchr.c			\
			ft_memcpy.c			\
			ft_memccpy.c		\
			ft_memmove.c		\
			ft_memcmp.c			\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_strlcpy.c		\
			ft_strdup.c			\
			ft_calloc.c			\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_strnstr.c		\
			ft_strjoin.c		\
			ft_split.c			\
			ft_substr.c			\
			ft_strtrim.c		\
			ft_itoa.c			\
			ft_strmapi.c		\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\

SRCS_BONUS	=	ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC		= gcc

CFLAGS	= -I -Wall -Wextra -Werror

$(NAME) :	$(OBJS)
	$(CC) $(CFLAGS) -c $(SRCS) -I libft.h
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all : $(NAME)

bonus : $(OBJS) $(OBJS_BONUS) 
	$(CC) $(CFLAGS) -c  $(SRCS) $(SRCS_BONUS) -I libft.h
	ar rc $(NAME) $(OBJS_BONUS) $(OBJS)
	ranlib $(NAME)

clean :
	rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean re
