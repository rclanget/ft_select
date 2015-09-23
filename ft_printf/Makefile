#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/18 15:07:41 by rclanget          #+#    #+#              #
#    Updated: 2015/09/18 15:07:46 by rclanget         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_PATH	=	./srcs/
SRC_NAME	=	ft_print_number.c ft_printf.c get_conv_info.c \
				print_int.c print_tools.c print_str.c print_utf.c \
				print_char.c print_double.c print_time.c ft_fdprintf.c 
OBJ_PATH	=	./obj/
INC_PATH	=	./includes/
NAME		=	./libftprintf.a
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: clean fclean re

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC) $(INC_PATH)*h