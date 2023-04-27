# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 22:37:07 by wbouwach          #+#    #+#              #
#    Updated: 2023/04/27 00:36:33 by oel-houm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
CC= cc
CFLAGS= -Wall -Wextra -Werror
RM= rm -rf
SRC=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isdigit ft_isprint\
		ft_memmove ft_memset ft_memchr ft_itoa ft_isascii ft_memcpy\
		ft_memcmp ft_split ft_strjoin ft_strtrim ft_strlcpy ft_putchar_fd\
		ft_putnbr_fd ft_putstr_fd ft_strrchr ft_strmapi ft_striteri ft_strnstr ft_substr\
		ft_tolower ft_toupper ft_strlen ft_strchr  ft_strcmp ft_strdup ft_putendl_fd ft_strncmp\

OBJ= $(SRC:=.o)

OBJ_B= $(B_SRC:=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $<

all: $(NAME)


$(NAME): $(OBJ) 
	@ar -rc $(NAME) $(OBJ) 

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all