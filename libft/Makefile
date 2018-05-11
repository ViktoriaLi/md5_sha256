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

NAME = libftprintf.a

HEADER = -c -I ./includes/

SFILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c \
ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_putendl_fd.c ft_strdel.c \
ft_strmapi.c ft_memalloc.c ft_putnbr.c ft_strequ.c ft_strnequ.c ft_memdel.c ft_putnbr_fd.c ft_striter.c \
ft_strnew.c ft_putchar.c ft_putstr.c ft_striteri.c ft_strsplit.c ft_putchar_fd.c ft_putstr_fd.c ft_strjoin.c \
ft_strsub.c ft_putendl.c ft_strclr.c ft_strmap.c ft_strtrim.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
ft_lstiter.c ft_lstmap.c ft_lstnew.c get_next_line.c ft_printf.c int_and_u.c hex.c \
check_params.c length_analize.c unicode.c octal.c atoi_and_itoa.c chars_handle.c flags_and_stars.c \
print_ints.c strings_handle.c additional_funcs.c

OFILES = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o ft_memccpy.o \
ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memmove.o ft_memset.o ft_strcat.o ft_strchr.o ft_strcmp.o ft_strcpy.o \
ft_strdup.o ft_strlcat.o ft_strlen.o ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnstr.o ft_strrchr.o ft_strstr.o \
ft_tolower.o ft_toupper.o ft_itoa.o ft_putendl_fd.o ft_strdel.o ft_strmapi.o ft_memalloc.o ft_putnbr.o ft_strequ.o \
ft_strnequ.o ft_memdel.o ft_putnbr_fd.o ft_striter.o ft_strnew.o ft_putchar.o ft_putstr.o ft_striteri.o ft_strsplit.o \
ft_putchar_fd.o ft_putstr_fd.o ft_strjoin.o ft_strsub.o ft_putendl.o ft_strclr.o ft_strmap.o ft_strtrim.o ft_lstadd.o ft_lstdel.o \
ft_lstdelone.o ft_lstiter.o ft_lstmap.o ft_lstnew.o get_next_line.o ft_printf.o int_and_u.o hex.o \
check_params.o length_analize.o unicode.o octal.o atoi_and_itoa.o chars_handle.o flags_and_stars.o print_ints.o strings_handle.o \
additional_funcs.o

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)

clean:
	rm -f $(OFILES) *.gch

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OFILES): %.o:%.c
	gcc -c -Wall -Wextra -Werror $(HEADER) $(SFILES) libft.h
