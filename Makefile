# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akarahan <akarahan@student.42istanbul.com. +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 15:44:43 by ysay              #+#    #+#              #
#    Updated: 2022/04/30 15:06:02 by akarahan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

_SRC = main.c arg.c arg2.c env.c env2.c other.c buildin.c path.c folder.c tok.c cd_cmd.c export_cmd.c echo_cmd.c \
	other_cmd.c split_logic.c split_folder.c split_quote.c cmd.c sign.c run.c utils.c dollar.c wildcard.c wildcard_utils.c \
	syntax.c

_OBJ = $(_SRC:.c=.o)
_EXLIB = libft.a
_IDIR = ./ ./libft

SDIR =
ODIR =
EXLIBD = libft/
IFLAG = -I

SRC = $(patsubst %,$(SDIR)%,$(_SRC))
OBJ = $(patsubst %,$(ODIR)%,$(_OBJ))
EXLIB = $(patsubst %,$(EXLIBD)%,$(_EXLIB))
INC = $(patsubst %,$(IFLAG)%,$(_IDIR))

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	RDLINE_LIB = -L$(HOME)/readline/lib -lreadline
	RDLINE_INC = -I/$(HOME)/readline/include/
else
	RDLINE_LIB = -lreadline
	RDLINE_INC =
endif

CC = gcc

FLAGS = -Wall -Wextra -Werror

DFLAG =

.PHONY: all debug clean fclean re dre

all: $(EXLIB) $(NAME)

debug: FLAGS += -fsanitize=address -g3
debug: DFLAG += debug
debug: $(EXLIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INC) $(RDLINE_INC) $(OBJ) $(EXLIB) $(RDLINE_LIB) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c
	$(CC) $(FLAGS) $(INC) $(RDLINE_INC) -c  $< -o $@

$(EXLIB):
	make -C $(EXLIBD) $(DFLAG)

clean:
	rm -rf $(OBJ)
	make clean -C $(EXLIBD)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(EXLIBD)

re: fclean all

dre: fclean debug
