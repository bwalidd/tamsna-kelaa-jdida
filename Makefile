NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline -L ./readline -I ./readline -lcurses


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


SRC = minishell \
		helpers/env \
		helpers/prompt \
		helpers/is_utils \
		parsing/parse \
		parsing/checker/check_oper \
		parsing/checker/check_chars \
		parsing/checker/check_pipe \
		parsing/checker/check_unsupport \
		parsing/add_space \
		parsing/split_args \
		parsing/token_input \
		parsing/parse_token \
		parsing/delete_quoate \
		parsing/expand/expand \
		parsing/expand/expand2 \


OBJ = $(SRC:=.o)

all: $(NAME) 

$(NAME): $(OBJ)
	@make bonus -C libft/
	@mv libft/libft.a .
	@$(CC) $(CFLAGS) $(READLINE) $(OBJ) -o $(NAME)

clean:
	@make clean -C libft/
	@rm -f $(OBJ)

fclean: clean`
	@make fclean -C libft/
	@rm -f libft.a
	@rm -f $(NAME)

re: fclean all