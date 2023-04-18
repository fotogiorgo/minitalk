# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 18:42:58 by jofoto            #+#    #+#              #
#    Updated: 2023/04/15 18:07:48 by jofoto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =			-Wall -Wextra -Werror -g -fsanitize=address

SRC_SERVER =	server.c

SRC_CLIENT =	client.c

OBJ_SERVER =	$(SRC_SERVER:%.c=%.o)

OBJ_CLIENT =	$(SRC_CLIENT:%.c=%.o)

NAME =			server

NAME_CLIENT =	client

LIBFT = libft/libft.a

all: $(NAME) $(NAME_CLIENT)

$(NAME): $(OBJ_SERVER) $(LIBFT)
	cc -o server $(OBJ_SERVER) $(FLAGS) $(LIBFT)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	cc -o client $(OBJ_CLIENT) $(FLAGS) $(LIBFT)

$(OBJ_CLIENT): %.o: %.c
	cc -c $? -o $@

$(OBJ_SERVER): %.o: %.c
	cc -c $? -o $@

$(LIBFT):
	cd libft && $(MAKE)

clean:
	rm -f $(OBJ_SERVER)
	rm -f $(OBJ_CLIENT)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_CLIENT)
	cd libft && $(MAKE) fclean

re: fclean all