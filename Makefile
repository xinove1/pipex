NAME= pipex

LIBFT = ./libft

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= pipex.c utils.c parser.c

BONUS_SRC = pipex_bonus.c utils.c parser.c here_doc_bonus.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) pipex.h
	make -C $(LIBFT)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a  -o $(NAME)

all: $(NAME)

bonus: $(BONUS_SRC) pipex.h
	make -C $(LIBFT)
	make -C $(LIBFT) bonus
	$(CC) $(CFLAGS) -c $(BONUS_SRC)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT)/libft.a  -o $(NAME)

clean:
	@make -C $(LIBFT) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME) $(BONUS_OBJ)

re: fclean all

.PHONY: clean fclean
