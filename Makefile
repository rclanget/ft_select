#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 18:39:36 by ulefebvr          #+#    #+#              #
#    Updated: 2015/09/21 14:53:45 by ulefebvr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRC_PATH	=	./srcs/
SRC_NAME	=	global.c parsing.c print.c term.c signal.c selection.c isatty.c main.c
OBJ_PATH	=	./obj/
INC_PATH	=	./includes/ ./libft/includes/ ./ft_printf/includes/
NAME		=	./ft_select
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH))
LIB_NAMES	=	-ltermcap ./libft/libft.a ./ft_printf/libftprintf.a
LDFLAGS		=	$(LIB_NAMES)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C ft_printf
	$(CC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make clean -C libft
	make clean -C ft_printf
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make fclean -C libft
	make fclean -C ft_printf
	rm -fv $(NAME)

re: fclean all
	make re -C libft
	make re -C ft_printf

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h