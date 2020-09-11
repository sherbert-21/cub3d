# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sherbert <sherbert@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/07 19:44:28 by sherbert          #+#    #+#              #
#    Updated: 2020/05/07 19:55:17 by sherbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

FLAGS	= -Wall -Werror -Wextra

INC = get_next_line.h

SRC = get_next_line.c \
get_next_line_utils.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re $(NAME)