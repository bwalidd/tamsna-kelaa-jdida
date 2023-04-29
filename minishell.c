/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/29 14:59:37 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int global_exit;





static int	number_of_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
		count++;
	return (--count);
}

static int	ft_isnum(char *str) // ft_isnum ft_isdigit
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void		exit_cmd(char **cmd) // exit_cmd takes 2 params: cmd + copy_of_env
{
	//
	//
	if (number_of_args(cmd) > 1)
	{
		//4-set exit status to 1
		if (cmd[1] && ft_isnum(cmd[1]) != 1)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmd[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            exit(255);
		}
		else if (cmd && ft_isnum(cmd[1]) == 1)
		{
            ft_putstr_fd("exit\n", 2);
            ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
	}
	else if (number_of_args(cmd) == 1)
	{
		if (!(ft_isnum(cmd[1])))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmd[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
		}
		int exit_value = ft_atoi(cmd[1]); //fix ft_atoi.c + change the value of $? in ENV
        //printf("exit\n");
		exit(exit_value);// check if cmd[1] is num then convert from char to int...
		//execvp(cmd[0], cmd);
	}
	else if (number_of_args(cmd) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

void	pwd_cmd(char **line)
{
	(void)line;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("getcwd"); //manage the error
	ft_putendl_fd(cwd, 1);
	free(cwd);
}

/*
 void   echo_cmd(char **line, int *t) // echo -n "omar el houmaadi" "salam www''haha" '485'
 {
    int i;
    int j;
    int jlen;

    i = 0;
    while (line[i])
    {
        if (t[i] == 2)
        {
            j = 0;
            jlen = ft_strlen(line[i]) - 1;
            //printf("%s = %d\n", line[i], jlen);
            while (line[i][j] && i < jlen)
            {
                if (((j == 0 && line[i][j] == '"') || (j == jlen && line[i][j] == '"'))) // ((j == 0 && line[i][j] == '\'') || (j == jlen && line[i][j] == '\'')))
                    j++;
                else if ((j == 0 && line[i][j] == '\'') || (j == jlen && line[i][j] == '\''))
                    j++;
                else
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
            }
            write(1, " ", 1);
        }
        //printf("%s == %d\n", line[i], t[i]);
        i++;
    }
    write(1, "\n", 1);
 }
 */

 void   echo_cmd(char **line, int *t) // echo -n "omar el houmaadi" "salam www''haha" '485'
 {
    int i;
    int j;
    int jlen;

    i = 0;
    while (line[i])
    {
        if (t[i] == 2)
        {
            j = 0;
            jlen = ft_strlen(line[i]) - 1;
            //while (line[i])
            //{
                // -n   -nnnn     dsfjsdjfjsdf -n
            if (line[i][j] == '-') 
                //
            else if (line[i][j] == '"' && line[i][jlen] == '"')
            {
                //write(1, "(1) ", 4);
                j = 1;
                 while (j < jlen)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
            } 
            else if (line[i][j] == '\'' && line[i][jlen] == '\'')
            {
                //write(1, "(2) ", 4);
                j = 1;
                while (j < jlen)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
            }
            else
            {
                //write(1, "(3) ", 4);
                j = 0;
                while (j < jlen + 1)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
            }
            write(1, " ", 1);
            //}
        }
        i++;
    }
    write(1, "\n", 1);
 }

void    parse_cmd(char **cmd, int *tokenised_cmd) //,token
{
    if (ft_strncmp(cmd[0], "exit", 4) == 0 && !cmd[0][4])
    {
        exit_cmd(cmd);
        int i = 0;
        while (cmd[i])
        {
            free(cmd[i]);
            i++;
        }
        free(cmd);
    }
    else if (ft_strncmp(cmd[0], "pwd" , 3) == 0 && !cmd[0][3])
    {
        pwd_cmd(cmd);
    }
    else if (ft_strncmp(cmd[0], "echo", 4) == 0 && !cmd[0][4])
    {
        echo_cmd(cmd, tokenised_cmd);
    }
}


int main(int ac, char **av, char **env)
{
    char *cmd;
    t_env *env_list;
    (void)av;
    if (ac > 1)
    {
        printf("Error: too many arguments\n");
        return (127);
    }
    env_list = create_env_list(env);
    //prompt(env_list);
    cmd = readline(BLUE"MINISHELL$ "WHITE);
    global_exit = 0;
    while (1)
    {
        if (*cmd)
            add_history(cmd);
        if (parse(cmd))
        {
            int i = 0;
            //printf("%s\n", parse_operator(cmd));
            //free(cmd);
            cmd = parse_operator(cmd);
            char **s = args_split(cmd);
            int *t = tokenise_cmd(s);
            // split cmd between pipes
           // while(s && s[i])
            //{
                //parse_cmd -> parse_builtins
                //printf("%s ===== %d\n",s[i],t[i]);
                //int j = 0;
                //while (s[j])
                //{
                 //   printf("%s\n", s[j]);
                  //  j++;
               // }
               parse_cmd(s, t);
               i++;
            //}
        }
       // prompt(env_list);
       // free(cmd);
        cmd = readline(BLUE"MINISHELL$ "WHITE);
    }
    
    return (global_exit);
}
