SRCS = $(wildcard *.c)	

OBJ = $(SRCS:.c=.o)

NAME = push_swap

CC = gcc 

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I ./libft/ -I . 

LIBS_PATH = -L ./libft 

LIBS = -lft

LIB_FT = ./libft/libft.a

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME): $(LIB_FT) $(OBJ)
	$(CC) $(CFLAGS) $(LIBS_PATH) $(OBJ) -o $(NAME) $(LIBS)

all: $(NAME)

$(LIB_FT):
	make libft.a -C ./libft/ 

clean:
	make clean -C ./libft/
	rm -rf $(OBJ)

fclean: clean
	make fclean -C ./libft/
	rm -rf $(NAME)
	rm -rf ./minishell.log

re: fclean all
