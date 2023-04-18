# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 18:42:58 by jofoto            #+#    #+#              #
#    Updated: 2023/04/18 20:41:23 by jofoto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS =				-Wall -Wextra -Werror -g -fsanitize=address

SRC_SERVER =		server.c

SRC_CLIENT =		client.c

OBJ_SERVER =		$(SRC_SERVER:%.c=%.o)

OBJ_CLIENT =		$(SRC_CLIENT:%.c=%.o)

SRC_SERVER_BONUS =	server_bonus.c

SRC_CLIENT_BONUS =	client_bonus.c

OBJ_SERVER_BONUS =	$(SRC_SERVER_BONUS:%.c=%.o)

OBJ_CLIENT_BONUS =	$(SRC_CLIENT_BONUS:%.c=%.o)

NAME =				server

NAME_CLIENT =		client

NAME_BONUS =		server_bonus

NAME_CLIENT_BONUS =	client_bonus

LIBFT = libft/libft.a

all: $(NAME) $(NAME_CLIENT)

bonus: $(NAME_BONUS) $(NAME_CLIENT_BONUS)

$(NAME): $(OBJ_SERVER) $(LIBFT)
	cc -o $(NAME) $(OBJ_SERVER) $(FLAGS) $(LIBFT)

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	cc -o $(NAME_CLIENT) $(OBJ_CLIENT) $(FLAGS) $(LIBFT)

$(NAME_BONUS): $(OBJ_SERVER_BONUS) $(LIBFT)
	cc -o $(NAME_BONUS) $(OBJ_SERVER_BONUS) $(FLAGS) $(LIBFT)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS) $(LIBFT)
	cc -o $(NAME_CLIENT_BONUS) $(OBJ_CLIENT_BONUS) $(FLAGS) $(LIBFT)

$(OBJ_CLIENT): %.o: %.c
	cc -c $? -o $@

$(OBJ_SERVER): %.o: %.c
	cc -c $? -o $@

$(OBJ_CLIENT_BONUS): %.o: %.c
	cc -c $? -o $@

$(OBJ_SERVER_BONUS): %.o: %.c
	cc -c $? -o $@

$(LIBFT):
	cd libft && $(MAKE)

clean:
	rm -f $(OBJ_SERVER)
	rm -f $(OBJ_CLIENT)
	rm -f $(OBJ_SERVER_BONUS)
	rm -f $(OBJ_CLIENT_BONUS)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_BONUS)
	rm -f $(NAME_CLIENT_BONUS)
	cd libft && $(MAKE) fclean

re: fclean all