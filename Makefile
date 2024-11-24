# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llebugle <lucas.lebugle@student.s19.be>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 16:31:53 by llebugle          #+#    #+#              #
#    Updated: 2024/10/28 12:43:48 by llebugle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h

CC = cc

SRCS = ft_printf.c		\
		conversion.c	\
		utils.c			\


OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

TEST_SRCS = test_ft_printf.c
TEST_NAME = test_ft_printf
TEST_OBJS = $(TEST_SRCS:.c=.o)

unit_test: $(NAME) $(TEST_OBJS)
	@$(CC) $(TEST_SRCS) -o $(TEST_NAME) -L. -lftprintf
	@echo "\033[0;34mRunning unit tests...\033[0m"
	@./$(TEST_NAME)
	@echo "\033[0;32mTests completed.\033[0m"

tests: unit_test

clean:
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re