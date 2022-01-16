NAME= pipex

LIBFT = ./libft

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC= pipex.c basic_utils.c pipex_utils.c

BONUS =

BONUS_OBJ = $(BONUS:.c=.o)

OBJ=$(SRC:.c=.o)

$(NAME): $(SRC) pipex.h
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT)/libft.a  -o $(NAME)

all: $(NAME)

bonus: $(BONUS_OBJ)

clean:
	@make -C $(LIBFT) clean
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME) $(BONUS_OBJ)

re: fclean all

.PHONY: clean fclean
