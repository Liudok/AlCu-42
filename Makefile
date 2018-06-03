#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/07 17:05:29 by lberezyn          #+#    #+#              #
#    Updated: 2018/01/16 15:34:04 by lberezyn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = alum1

SRC = src/main.c \
      src/parser.c \
      src/algo.c \
      src/utils.c \

OFILES = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

all: $(NAME)

%.o : src/%.c include/alcu.h
	@clang $(FLAG) -o $@ -c $<

$(NAME): $(OFILES) include/alcu.h
	@make -C libft
	@clang $(FLAG) -L./libft -lft $(OFILES) -o $(NAME)
	@echo "$(NAME) SUCCESSFULLY compiled"

clean:
	rm -f $(OFILES)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re
