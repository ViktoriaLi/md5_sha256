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

INC_DIR := ./includes/
LIB_DIR := ./libft/

SFILES := main.c reading.c init_vectors.c md5.c sha256.c sha512.c printing.c \
 				 bits_shifting.c last_rounds_md5.c flags_ssl.c

OFILES := main.o reading.o init_vectors.o md5.o sha256.o sha512.o printing.o \
				 bits_shifting.o last_rounds_md5.o flags_ssl.o

LIBFT = $(LIBFT_DIR)libftprintf.a
LIBFT_DIR := $(LIB_DIR)
LIBFT_INC := $(LIBFT_DIR)includes/
LIBFT_FLAGS :=  -lft -L $(LIBFT_DIR)

CC_FLAGS := -Wall -Wextra -Werror
LINK_FLAGS := $(LIBFT_FLAGS)
HEADER_FLAGS := -I $(INC_DIR)  -I $(LIBFT_INC)

CC_FLAGS := -Wall -Wextra -Werror
CC := gcc

all: $(NAME)

$(NAME): $(LIBFT) $(OFILES)
	$(CC) $(OFILES) $(LINK_FLAGS) -o $(NAME) libftprintf.a

$(OFILES): %.o:%.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OFILES)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
