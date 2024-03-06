# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 00:15:13 by haalouan          #+#    #+#              #
#    Updated: 2024/01/12 02:33:49 by haalouan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = client
NAME2 = server
BNAME1 = client_bonus
BNAME2 = server_bonus

SRCS1 = client.c utils.c utils2.c
SRCS2 = server.c utils.c utils2.c
BSRCS1 = client_bonus.c utils.c utils2.c
BSRCS2 = server_bonus.c utils.c utils2.c

CC = cc
FLAGS = -Wall -Wextra -Werror

OBJ1 = ${SRCS1:.c=.o} 
OBJ2 = ${SRCS2:.c=.o} 
BOBJ1 = ${BSRCS1:.c=.o} 
BOBJ2 = ${BSRCS2:.c=.o} 

all : $(NAME1)	$(NAME2)

$(NAME1): $(OBJ1)
	$(CC) $(FLAGS) -o $@ $^

$(NAME2): $(OBJ2)
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c minitalk.h
	$(CC) $(FLAGS) -c $< -o  $@

bonus:	$(BNAME1) $(BNAME2)

$(BNAME1): $(BOBJ1)
	$(CC) $(FLAGS) -o $@ $^

$(BNAME2): $(BOBJ2)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -f $(OBJ1) $(OBJ2) $(BOBJ1) $(BOBJ2)
	
fclean: clean
	rm -f $(NAME1) $(NAME2) $(BNAME1) $(BNAME2)

re: fclean all

.PHONY: clean