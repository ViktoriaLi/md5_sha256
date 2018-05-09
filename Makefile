#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/27 15:23:08 by vlikhotk          #+#    #+#              #
#    Updated: 2017/11/02 15:15:21 by vlikhotk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ssl

SFILES = main.c reading.c init_vectors.c md5.c sha256.c sha512.c printing.c

OFILES = main.o reading.o init_vectors.o md5.o sha256.o sha512.o printing.o

all: $(NAME)

$(NAME): $(OFILES)

$(OFILES): %.o:%.c
	gcc -c -Wall -Wextra -Werror $(SFILES)

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all
