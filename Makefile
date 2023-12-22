# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/22 08:16:20 by TheDeagle         #+#    #+#              #
#    Updated: 2023/12/22 08:21:14 by TheDeagle        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

S_SRC = server.c
S_OBJ = server.o
C_SRC = client.c
C_OBJ = client.o

all: $(SERVER) $(CLIENT)

$(SERVER): $(S_OBJ)
	$(CC) $(CFLAGS) $(S_SRC) -o $(SERVER)

$(CLIENT): $(C_OBJ)
	$(CC) $(CFLAGS) $(C_SRC) -o $(CLIENT)


clean:
	rm -f $(C_OBJ) $(S_OBJ)

fclean: clean
	rm -rf $(SERVER) $(CLIENT)

re: fclean $(SERVER) $(CLIENT)