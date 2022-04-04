# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 15:44:43 by ysay              #+#    #+#              #
#    Updated: 2022/04/04 12:27:15 by akarahan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

_SRC= main.c arg.c arg2.c env.c env2.c other.c buildin.c path.c folder.c tok.c cd_cmd.c export_cmd.c echo_cmd.c \
	other_cmd.c split_logic.c split_folder.c split_quote.c cmd.c sign.c run.c utils.c dollar.c wildcard.c wildcard_utils.c \
	syntax.c

_OBJ= $(_SRC:.c=.o)
_EXLIB= libft.a
_IDIR= ./ ./libft

SDIR=
ODIR=
EXLIBD=libft/
IFLAG= -I

SRC= $(patsubst %,$(SDIR)%,$(_SRC))
OBJ= $(patsubst %,$(ODIR)%,$(_OBJ))
EXLIB= $(patsubst %,$(EXLIBD)%,$(_EXLIB))
INC= $(patsubst %,$(IFLAG)%,$(_IDIR))

CC= gcc

FLAGS= -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(EXLIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INC) $(EXLIB) -L$(HOME)/readline/lib -lreadline -I/$(HOME)/readline/include/ $(OBJ) -o $(NAME)

$(ODIR)%.o : $(SDIR)%.c
	$(CC) $(FLAGS) $(INC) -I/$(HOME)/readline/include/ -c  $< -o $@

$(EXLIB) :
	make -C $(EXLIBD)

clean:
	rm -rf $(OBJ)
	make clean -C $(EXLIBD)
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(EXLIBD)
re: fclean all
