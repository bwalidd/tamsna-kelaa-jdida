/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/01 21:43:23 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int global_exit;


int find_env(char *env, t_env *env_list)
{
    size_t  i;
    int     len;

    len = ft_strlen(env);
    i = 1;
    while (env_list != NULL)
    {
        if (ft_strncmp(env_list->env_name, env, len) == 0)
        {
            if (ft_strncmp(&env_list->env_name[len + 1], "=", 0) == 0)
                return (i);
            i++;
        }
        else
            i++;
        env_list = env_list->next;
    }
    return (0);
}

void    set_env(char *env_name, char *env_value, t_env *env_list) // new_env_value 
{
    //size_t  i;
    int     env_len;
    //char    *tmp;
    //char    *new;
    
    if (!env_name || !env_value)
        return ;
    env_len = ft_strlen(env_name);
    if (find_env(env_name, env_list) > 0) // remove this condition #EXPORT_FIX
    {
        while (env_list->env_name)
        {
            if (ft_strncmp(env_list->env_name, env_name, env_len) == 0)
            {
                //free(env_list->env_value);
                //env_list->env_value = env_value;
            }
            env_list = env_list->next;
        }
    }
}


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


int     check_n_sequence(char *str)
{
    int i;

    i = 0;
    if (str[i] != '-')
        return (0);
    i++;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void   echo_cmd(char **line, int *t)
{
    int i;
    int j;
    int jlen;
    int flag_n;
    int flag_ = 0;

    i = 0;
    flag_n = 0;
    while (line[i])
    {
        if (t[i] == 2)
        {
            j = 0;
            jlen = ft_strlen(line[i]) - 1;
            if ((ft_strncmp(line[i], "-n", 2) == 0 || check_n_sequence(line[i]) == 1) && flag_ == 0)
            {
                if (check_n_sequence(line[i]) == 0)
                {
                    int j;

                    j = 0;
                    while (line[i][j])
                    {
                        write(1, &line[i][j], 1);
                        j++;
                    }
                    if (line[i + 1] != NULL)
                        write(1, " ", 1);
                    flag_n = 0;
                }
                else
                    flag_n = 1;
            }
            /*else if (line[i][j] == '"' && line[i][jlen] == '"')
            {
                j = 1;
                 while (j < jlen)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
            }
            else if (line[i][j] == '\'' && line[i][jlen] == '\'')
            {
                j = 1;
                while (j < jlen)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
            }*/
            else
            {
                flag_ = 1;
                j = 0;
                while (j < jlen + 1)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
                //write(1, " ", 1);
                //if (line[i + 1] != NULL && !(i == 1 && flag_n == 1))
                if (line[i + 1] != NULL)
                {
                    write(1, " ", 1);
                }
            }
            
        }
        i++;
    }
    if (flag_n == 0)
        write(1, "\n", 1);
    // remove the flag_ #FIX
 }

void    env_cmd(char **cmd, t_env *env_list)
{
    (void)cmd;
    while (env_list != NULL)
    {
        ft_putstr_fd(env_list->env_name, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(env_list->env_value, 1);
        ft_putstr_fd("\n", 1);
        env_list = env_list->next;
    }
}

void    cd_cmd(char **cmd, t_env *env_list)
{
    //if (**char args && args[1] && args[2])
    // then print "error: too many arguments" + exit(1)
    int     ret;
    char    *path;
    char    *pwd;
    //printf("d=%d\n", find_env(cmd[1], env_list));

    // cd ./project313/42network
    // add in $OLDPWD and $PWD
    pwd = getcwd(NULL, 0);
    path = ft_strdup(cmd[1]);
    if (cmd[0] && !cmd[1])
    {
        write(1, "begin\n", 1);
        ret = chdir("/Users/oel-houm");
        write(1, "finish\n", 1);
    }
    else
        ret = chdir(path);
    (void)env_list;
    if (ret == -1) // if chdir() returns -1, it means that the directory could not be changed.
        perror("chdir error"); // using perror to print the error message to the console.
    /* else
    {
        // update the PWD environment variable with the new directory path using the setenv()
        // we have also update the OLDPWD environment variable with the previous directory path.
        if (pwd)
        {
            //set_env("OLDPWD", pwd, env_list);
            free(pwd);
        }
        if ((pwd = getcwd(NULL, 0)))
        {
            //set_env("PWD", pwd, env_list);
            free(pwd);
        }
        //printf("PWD=%s\n", get_env_value("PWD"));
        //printf("OLDPWD=%s\n", get_env_value("OLDPWD"));
        
        ft_putstr_fd("PWD=", 1);
        ft_putstr_fd(" ", 1);
        ft_putstr_fd("\n", 1);
        ft_putstr_fd("OLDPWD=", 1);
        ft_putstr_fd(" ", 1);
        ft_putstr_fd("\n", 1);
        
    }
    return ; */
    // free(pwd);
    

    // printf("ret=%d\n", ret);
}

void    parse_cmd(char **cmd, int *tokenised_cmd, t_env *env_list) //,token
{
    if (ft_strncmp(cmd[0], "exit", 4) == 0 && !cmd[0][4])
    {
        (void)env_list;
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
        (void)env_list;
        pwd_cmd(cmd);
    }
    else if (ft_strncmp(cmd[0], "echo", 4) == 0 && !cmd[0][4])
    {
        (void)env_list;
        delete_quoate(cmd);
        echo_cmd(cmd, tokenised_cmd);
    }
    else if (ft_strncmp(cmd[0], "env", 3) == 0 && !cmd[0][3])
    {
        env_cmd(cmd, env_list);
    }
    else if (ft_strncmp(cmd[0], "cd", 2) == 0 && !cmd[0][2])
    {
        cd_cmd(cmd, env_list);
    }
}

int main(int ac, char **av, char **env)
{
    // cd with only a relative or absolute path
    // export with no options
    // unset with no option
    // exit with no options
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
               parse_cmd(s, t, env_list);
               i++;
            //}
        }
       // prompt(env_list);
       // free(cmd);
        cmd = readline(BLUE"MINISHELL$ "WHITE);
    }
    
    return (global_exit);
}
