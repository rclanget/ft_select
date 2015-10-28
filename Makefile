#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 18:39:36 by ulefebvr          #+#    #+#              #
#    Updated: 2015/10/28 17:30:44 by ulefebvr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_PATH	=	./srcs/
SRC_NAME	=	global.c parsing.c print.c term.c signal.c selection.c \
				isatty.c main.c
OBJ_PATH	=	./obj/
INC_PATH	=	./includes/ ./libft/includes/
NAME		=	./ft_select
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH))
LIB_NAMES	=	-ltermcap ./libft/libft.a
LDFLAGS		=	$(LIB_NAMES)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make clean -C libft
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make fclean -C libft
	rm -fv $(NAME)

re: fclean all
	make re -C libft

norme:
	norminette $(SRC)
	norminette $(INC_PATH)