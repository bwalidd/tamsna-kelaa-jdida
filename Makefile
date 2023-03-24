NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline -L ./readline -I ./readline -lcurses


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


SRC = minishell helpers/env helpers/prompt parsing/parse


OBJ = $(SRC:=.o)

all: $(NAME) 

$(NAME): $(OBJ)
	@make bonus -C libft/
	@mv libft/libft.a .
	@$(CC) $(CFLAGS) $(READLINE) $(OBJ) -o $(NAME)

clean:
	@make clean -C libft/
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft/
	@rm -f libft.a
	@rm -f $(NAME)

re: fclean all