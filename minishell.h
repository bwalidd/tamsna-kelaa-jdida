/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 21:59:40 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/25 02:00:42 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H
# define BLUE "\033[1;34m"
# define WHITE "\033[0m"
# define GREEN "\033[0;32m"
# define PURPLE "\033[0;35m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
//# include "/usr/include/readline/readline.h"
//# include "/usr/include/readline/history.h"
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

# define STDIN 	0
# define STDOUT 1
# define STDERR 2

typedef struct s_global_vars
{
	int	num_of_cmds;
}	t_global_vars;

typedef struct s_env
{
	char    		*env_name;
	char    		*env_value;
	int				unset;
	struct s_env 	*next;
	struct s_env 	*prev;
}               t_env;

typedef	struct	s_cmd_data
{
	char	**parsed_line_args;
	int		num_of_cmds;
	int		*args_tokens;
	char	***cmd;
	int		stdout_copy;
	int		stdin_copy;
	int		i;
} t_cmd_data;

typedef struct s_redirection
{
	// input redirection vars
	int		in_redirection_token;
	int		in_redirection_index;
	int		infile_index;
	int		in_fd;
	char	*infile;
	//	output redirection vars
	int		out_redirection_token;
	int		out_redirection_index;
	int		outfile_index;
	int		out_fd;
	char	*outfile;

	int		stdin_copy;
	int		stdout_copy;
}	t_redirection;

/*
void	init_cmd_data(t_cmd_data *cmd_data)
{
	line = parse_operator(line);
	cmd_data->parsed_line_args = args_split(line);
	cmd_data->num_of_cmds = count_cmds(parsed_line_args, '|');;
	cmd_data->args_tokens = tokenise_cmd(parsed_line_args);;
	cmd_data->cmd = get_piped_cmd_by_ptr(parsed_line_args, args_tokens);
	cmd_data->stdout_copy = dup(STDOUT);;
	cmd_data->stdin_copy = dup(STDIN);
	cmd_data->i = 0;
	(void)cmd_data->stdin_copy;
} */

extern int global_exit;

typedef enum e_token //this
{
	CMD_NAME = 1,	//	
	CMD_ARG, 		//	
	R_IN_SIG,		//	<
	R_OUT_SIG,		//	>
	R_OUT_FILE,		//	
	PIPE,			//	
	R_APP_SIG,		// >>	
	R_APP_FILE,		//	
	R_IN_FILE,		//	
	HEREDOC_SIG,	//	<<
	HEREDOC_LIM,	//	
	EMPTY,			//	
}	t_token;


 /* utils  */
int		main(int ac, char **av, char **env);
void	prompt(t_env *env_list);
int		is_redirection(char c);
int		is_space(char c);
int		ft_array_size(char **array_str);
int     ft_envlst_len(t_env *env_list);
int		ft_strlenn(char *s);

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
char	*apply_expander(char *cmd, t_env *env);
char    *replacing(char *cmd, int *i);
char	*replace_wrong_name(char *cmd, int *i);
void    delete_quoate(char **cmd);
int		check_oper_in_last(char *line ,char c);

/*  builtins */

void	exit_cmd(char **cmd);
void	pwd_cmd(char **line);
void	unset_cmd(char **cmd, t_env *env_list);
void	echo_cmd(char **line, int *tokens);
void	env_cmd(char **cmd, t_env *env_list);
void    export_cmd(char **cmd, t_env *env_list);
void    cd_cmd(char **cmd, t_env *env_list);

//void	piping_child_cmd(char *cmd, char **env);


void    piping(char **cmd, int infile, int outfile, char **env, t_env *env_list, int *token);
char	*get_cmd_path(char *cmd, char **env);
char	*path_join(char *dir, char *cmd);
char	*get_cmd_path(char *cmd, char **env);
void     exec_builtins(char **cmd, int *tokens, t_env *env_list);
int     is_builtins(char *cmd);
void    exec_cmd(char **cmd_args, char **env);

void	multi_pipes_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list);

char    *get_env_value(char *env_var, t_env *env_list);
int		find_env(char *env, t_env *env_list);
void    set_env(char *env_name, char *env_value, t_env *env_list);


char	***get_piped_cmd_by_ptr(char **cmds, int *tokens);
int		count_cmds(char **cmd, char c);

void	check_fork_fail(pid_t *pid);

void    single_cmd_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list);

// typedef	struct s_global_vars
// {
// 	char	**parsed_line_args;
// 	int		num_of_cmds;
//     int		*args_tokens;
//     char	***cmd;
//     int		i;
//     int		out_fd;
//     int		stdout_copy;
//     int		stdin_copy;
// }	t_var; // cmd_exec_vars



void	set_output_redirect_to_null(char **cmd, int *cmd_tokens);
int		get_output_redirection_index(int *cmd_tokens, t_redirection *redirection);
int		get_outfile_index(int *cmd_tokens, int index);
void	establish_output_stream(char **cmd, int *cmd_tokens, t_redirection *redirection);

void    establish_input_stream(char **cmd, int *cmd_tokens, t_redirection *redirection);

void	dup_input_before_piping(t_redirection *redirection);
void	dup_input_after_piping(t_redirection *redirection);
void	dup_output_before_piping(t_redirection *redirection);
void	dup_output_after_piping(t_redirection *redirection);

void    check_argc(int ac);
void    cmd_not_found(char *cmd, int *global_exit);

void    single_cmd_execution1(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list);
void	init_cmd_data(t_cmd_data *cmd_data, char *line);


void    establish_io_stream(char **cmd, int *cmd_tokens, t_redirection *redirection);
void    dup_io_before_piping(t_redirection *redirection);

void	execute_line(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list, char *line);

#endif