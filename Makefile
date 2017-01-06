# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rclanget <rclanget@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/16 18:39:36 by rclanget          #+#    #+#              #
#    Updated: 2017/01/06 18:28:08 by rclanget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	@make -C libft
	@$(CC) $(LDFLAGS) $(OBJ) -o $@ && \
		printf " -->> \033[32mCompilation Success: %s\033[0m             \n" "$@"|| \
		printf " -->> \033[31mCompilation Failed: %s\033[0m              \n" "$@";

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) && \
		printf " -->> \033[32mOk\033[0m: %s                       \r" "$@" || \
		printf " -->> \033[31mKo\033[0m: %s                       \r" "$@";

clean:
	@make clean -C libft
	@rm -rfv $(OBJ_PATH)

fclean: clean
	@make fclean -C libft
	@rm -fv $(NAME)

re: fclean all
	@make re -C libft

norme:
	@norminette $(SRC)
	@norminette $(INC_PATH)
