/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/05 23:10:57 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
┌──(toowan㉿toowan)-[~]
└─$ unset LS_COLOR*                     
unset: LS_COLOR*: invalid parameter name
*/

#include "minishell.h"

int global_exit;

char    *get_env_value(char *env_var, t_env *env_list)
{
    int env_len;

    if (!env_var)
        return (NULL);
    env_len = ft_strlen(env_var);
    while (env_list->env_name)
    {
        if (ft_strncmp(env_list->env_name, env_var, env_len) == 0)
        {
            return (env_list->env_value);
            break ;
        }
        env_list = env_list->next;
    }
    return (NULL);
}

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

// set env_value on the specified env_name
void    set_env(char *env_name, char *env_value, t_env *env_list) // new_env_value 
{
    //size_t  i;
    int     env_len;
    char    *env;
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
                free(env_list->env_value);
                env = ft_strdup(env_value); // leaks-fix
                env_list->env_value = env;
                break ;
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

void   echo_cmd(char **line, int *t) // remove the flag_ #FIX
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
            else
            {
                flag_ = 1;
                j = 0;
                while (j < jlen + 1)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
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
 }

void    env_cmd(char **cmd, t_env *env_list) // deny printing equal character "=" ila env_name & env_vaue dont exist in case of (unset var)
{
    (void)cmd;
    while (env_list != NULL)
    {
        if (env_list->unset != 1)
        {
            ft_putstr_fd(env_list->env_name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(env_list->env_value, 1);
            ft_putstr_fd("\n", 1);
        }
        env_list = env_list->next;
    }
}

void    cd_cmd(char **cmd, t_env *env_list)
{
    //if (**char args && args[1] && args[2])
    // then print "error: too many arguments" + exit(1)
    // printf("d=%d\n", find_env(cmd[1], env_list));
    // cd ./project313/42network
    // add in $OLDPWD and $PWD

    // KAYN WA7D LPROBLEM MNIN KANDIR UNSET PATH, PWD, OLDPWD
        // khassni nzid export PWD=$PATH instead of dak tkhrbi9 li dayr 
    int     ret;
    char    *path;
    char    *pwd;
    pwd = getcwd(NULL, 0);
    ret = 0;
    if (cmd[0] && !cmd[1])
        ret = chdir("/Users/oel-houm");
    else
    {
        path = ft_strdup(cmd[1]);
        ret = chdir(path);
    }
    (void)env_list;
    if (ret == -1) // if chdir() returns -1, it means that the directory could not be changed.
        perror("chdir error"); // using perror to print the error message to the console.
    else
    {
        if (pwd)
        {
            set_env("OLDPWD", pwd, env_list);
            free(pwd);
        }
        if ((pwd = getcwd(NULL, 0)))
        {
            set_env("PWD", pwd, env_list);
            free(pwd);
        }
        // ft_putstr_fd("PWD=", 1);
        // ft_putstr_fd(get_env_value("PWD", env_list), 1);
        // ft_putstr_fd("\n", 1);
        // ft_putstr_fd("OLDPWD=", 1);
        // ft_putstr_fd(get_env_value("OLDPWD", env_list), 1);
        // ft_putstr_fd("\n", 1);
    }
    return ;
    // free(pwd);
}

void    print_export_string(char *str)
{
    int     i;

    i = 0;
    while (str[i] != '=' && str[i] != '\0')
    {
        write(2, &str[i], 1);
        i++;
    }
}

int     is_allowed(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != '=')
    {
        if ((str[i] >= 33 && str[i] <= 47) ||
            (str[i] >= 58 && str[i] <= 64) ||
            (str[i] >= 91 && str[i] <= 96) ||
            (str[i] >= 123 && str[i] <= 126))
            return (0);
        i++;
    }
    return (1);
}

// ft_strdup(char *str, char limiter, )

void    do_export(char *str, t_env *env_list)
{// export name=omar
 // export name=  
    //(void)env_list;
    int var_len;
    int value_len;
    int flag;
    int i;

    i = 0;
    flag = 0;
    var_len = 0;
    value_len = 0;
    while (str[i])
    {
        //flag++;
        if (str[i] == '=')
            break ;
        i++;
    }
    var_len = i;
    if (str[i] == '=' && str[i + 1])
    {
        flag++; // flag = 1 doens't work in some compilers
        i++;
    }
    while (str[i])
    {
        value_len++;
        i++;
    }
    // if varlen > and valuelen != 0 and .... then export to
    // printf("str: %s\n", str);
    // printf("var_len: %d\n", var_len);
    // printf("value_len: %d\n", value_len);
    char *var = malloc(sizeof(char) * var_len + 1 );
    char *val = malloc(sizeof(char) * value_len + 1);
    i = 0;
    while (i < var_len)
    {
        var[i] = str[i];
        i++;
    }
    var[i] = '\0';
    i = 0;
    str = &str[var_len + 1];
    while (*str)
    {
        val[i] = *str;
        //printf("%c-", val[i]);
        i++;
        str++;
    }
    val[i] = '\0';

    //check if the var is already kayn f 
    t_env   *tail_env;
    //while (env_list->next != NULL)
    while (env_list != NULL)
    {
        if (env_list->next == NULL)
            tail_env = env_list;
        if (ft_strncmp(env_list->env_name, var, var_len) == 0)
            env_list->unset = 1;
        env_list = env_list->next;
    }

    t_env   *new_env;
    new_env = malloc(sizeof(t_env));
    new_env->env_name = var;
    new_env->env_value = val;
    new_env->unset = 0;

    //new_env->prev = env_list;
    new_env->prev = tail_env;
    new_env->next = NULL;
    tail_env->next = new_env;
    //printf("str: %s\n", str);
    //printf("var= %s\n", env_list->env_name);
    //printf("val= %s\n", env_list->env_value);
    //printf("prev_var= %s\n", env_list->prev->env_name);
    //printf("prev_val= %s\n", env_list->prev->env_value);
    //printf("var_len: %d\n", var_len);
    //printf("value_len: %d\n", value_len);
}
// check if the varname already is in the env
// ila kan exist ghnbdel lih gha value dyalo safi
// ila nn ghansawb var & val mn jdid

// allowed begin char
int     if_allowed(char *str, t_env *env_list) // export_checker //check begin // check export arg
{
    //  .=value
    //  u.u=value
    //  98=value
    //  _uuu=value
    // letter=value
    int     i;

    i = 1;
    if (!ft_isalpha(str[0]) && str[0] != '_')
    {
        while (str[i] != '\0' && str[i] != '=')
        {
            if (str[0] >= 48 && str[0] <= 57)
            {
                ft_putstr_fd("minishell: export: `", 2);
                print_export_string(str);
                ft_putstr_fd("': not a valid identifier\n", 2);
                return (0);
            }
            else if ((str[0] >= 33 && str[0] <= 47) ||
                (str[0] >= 58 && str[0] <= 64) ||
                (str[0] >= 91 && str[0] <= 96) ||
                (str[0] >= 123 && str[0] <= 126))
            {
                ft_putstr_fd("minishell: export: `", 2);
                print_export_string(str);
                ft_putstr_fd("': not a valid identifier\n", 2);
                return (0);
            }
            i++;
        }
    }
    else
    {
        if (is_allowed(&str[i]) == 1)
        {
            do_export(str, env_list);
        }
        else
        {
            ft_putstr_fd("minishell: export: `", 2);
            print_export_string(str);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
        
    }
    return (0);
}

void    export_cmd(char **cmd, t_env *env_list) // export var1=abc var2=xyz fkd5sfd5fs  tty=565           export_cmd += t_env env_list
// export _=abc x2=jdfjg x3=fjghjfdg   djfhdshfjdhshhjdsghjdfjg  x5=kfgjfdg x6=fjdfghdfg -a -q -o
{
    int i;
    i = 1;
    if (cmd[0] && !cmd[1])
    {
        write(1, "", 1); // export loop !!!!!!!!!
    }
    /////////////////////   FIX this   //////////////////////////
    else
    {
        //while (cmd[i] != '\0' || cmd[i] != '=')
        while (cmd[i])
        {
            if (if_allowed(cmd[i], env_list) == 1)
            {
                ft_putstr_fd(cmd[i], 1);
                ft_putstr_fd("\tallowed\n", 1);
            }
            else
                write(1, "fake\n", 5);
            i++;
        }
    }
    ////////////////////////////////////////////////////////////
    // after fixing export + cmd[1]
    while (cmd[i])
    {
        printf("%s\n", cmd[i]);
        i++;
    }
    return ;
}

void    unset_cmd(char **cmd, t_env *env_list)
{
    // cmdlen env_len !
    // convert $VAR to string then pass it to be executed
    int     i;
    int     cmd_len;
    int     env_len;
    int     n;
    t_env   *env_header;

    env_header = env_list;
    i = 1;
    while (cmd[i])
    {
        env_list = env_header;
        cmd_len = ft_strlen(cmd[i]);
        while (env_list != NULL)
        {
            env_len = ft_strlen(env_list->env_name); // unset name unset name _ SCHOOL42 MAIL42 USER42
            //if ((ft_strncmp(cmd[i], env_list->env_name, cmd_len) == 0) && (env_len == cmd_len))
            // ndir comparison nchof chkon li kbrf len wahc cmd wla envlen o li kbr howa li ydoz f conditin li lt7t as size_t n;
            if (env_len > cmd_len)
                n = env_len;
            else
                n = cmd_len;
            if ((ft_strncmp(cmd[i], env_list->env_name, n) == 0) && env_list->unset != 1)
            {
                printf("cmd=%s\tenv=%s\tn=%d\n", cmd[i], env_list->env_name, n);
                env_list->unset = 1;
                //printf("%d\t%s\n", env_list->unset, env_list->env_name);
                break ;
            }
            else
                //printf("cmd=%s\tcmdlen=%d\t\tenv=%s\tenvlen=%d\n", cmd[i], cmd_len, env_list->env_name, env_len);
            env_list = env_list->next;
        }
        i++;
    }
    return ;
}
// unset SHELL OLDPWD PWD TERM PAGER LS_COLORS LSCOLORS USERLOGIN HOME TMPDIR LANG SHLVL LESS MallocNanoZone _ ZSH ORIGINAL_XDG_CURRENT_DESKTOP SSH_AUTH_SOCK Apple_PubSub_Socket_Render LOGNAME USER COMMAND_MODE COLORTERM XPC_FLAGS ZDOTDIR SECURITYSESSIONID  GIT_ASKPASS XPC_SERVICE_NAME USER_ZDOTDIR __CF_USER_TEXT_ENCODING TERM_PROGRAM TERM_PROGRAM_VERSION                        
// PATH

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
        cd_cmd(cmd, env_list); // KAYN WA7D LPROBLEM MNIN KANDIR UNSET PATH, PWD, OLDPWD
        // khassni nzid export PWD=$PATH instead of dak tkhrbi9 li dayr 
    }
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
    {
        export_cmd(cmd, env_list);
    }
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
    {
        unset_cmd(cmd, env_list);
    }
    else
        write(1, ":(\n", 3);
}

int main(int ac, char **av, char **env)
{
    // cd with only a relative or absolute path
    // export with no options
    // unset with no option
    // exit with no options
    (void)ac;
    (void)av;
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
