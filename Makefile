NAME= pipex

LIBFT = ./libft

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= pipex.c utils.c parser.c here_doc.c

BONUS = 0

BONUS_OBJ = $(BONUS:.c=.o)

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) pipex.h
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -D BONUS=$(BONUS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a  -o $(NAME)

all: $(NAME)

bonus: BONUS=1
bonus: $(NAME)

clean:
	@make -C $(LIBFT) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME) $(BONUS_OBJ)

re: fclean all

.PHONY: clean fclean
