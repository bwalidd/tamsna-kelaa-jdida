/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:59:40 by wbouwach          #+#    #+#             */
/*   Updated: 2023/03/23 02:52:35 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BLUE "\033[1;34m"
# define WHITE "\033[0m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_env
{
	char    *env_name;
	char    *env_value;
	struct s_env *prv;
	struct s_env *next;
}               t_env;



typedef enum token
{
	CMD_NAME = 1,
	CMD_ARG,
	R_IN_SIG,
	R_OUT_SIG,
	R_OUT_FILE,
	PIPE,
	R_APP_SIG,
	R_APP_FILE,
	R_IN_FILE,
	HEREDOC_SIG,
	HEREDOC_LIM,
	EMPTY,
}	t_token;


 /* utils  */
int		main(int ac, char **av, char **env);
void	prompt(t_env *env_list);
int is_redirection(char c);
int is_space(char c);
int	ft_array_size(char **array_str);

/*  env   */

t_env	*create_env_list(char **env);
t_env	*ft_envlst_new(char *str);
t_env	*ft_envlst_search(t_env *env, char *searched);

/*  parsing */

int		parse(char *line);
int		check_pipe(char *line);
int		check_oper(char c, char *line, int nb);
int		check_chars(char *line, char *str);
int		check_unsupport(char *line);
void	quoate_flag(int *flag, int c);
char    *parse_operator(char *line);
char    **args_split(char *cmd);
int		*tokenise_cmd(char **cmd);
int		parse_token(int *token_arr);
void    expand(char **cmd,int *token_arr,t_env *env);
char    *replacing(char *cmd, int *i);
char	*replace_wrong_name(char *cmd, int *i);
#endif
