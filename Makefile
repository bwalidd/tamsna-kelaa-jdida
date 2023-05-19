NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
#READLINE = -lreadline -L ./readline -I ./readline -lcurses
READLINE = -L /usr/lib/x86_64-linux-gnu -lreadline -lncurses
LDLIBS = -lreadline -lncurses

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ 

SRC = minishell \
		helpers/env \
		helpers/prompt \
		helpers/is_utils \
		helpers/ft_strlenn \
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
		execution/unset \
		execution/exit \
		execution/pwd \
		execution/echo \
		execution/cd \
		execution/export \
		execution/env \


OBJ = $(SRC:=.o)

all: $(NAME) 

$(NAME): $(OBJ)
	@make -s -C libft/
	@mv libft/libft.a .
	@$(CC) $(CFLAGS) $(READLINE) $(OBJ) -o $(NAME) libft.a
	@echo "\033[3;32mminishell is ready\033[0m"

clean:
	@make -s clean -C libft/
	@rm -f $(OBJ)

fclean: clean
	@make -s fclean -C libft/
	@rm -f libft.a
	@rm -f $(NAME)

re: fclean all
