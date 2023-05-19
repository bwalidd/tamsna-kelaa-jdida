/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/19 03:41:16 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
        cd_cmd(cmd, env_list);
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
        export_cmd(cmd, env_list);
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        unset_cmd(cmd, env_list);
    else
        write(1, ":(\n", 3);
}

int	count_cmds(char **cmd, char c)
{
	int	i;
	int	trigger;
	int	count;

	(void)c;
	i = 0;
	trigger = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i]) + 1) != 0 && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])) == 0)
			trigger = 0;
		i++;
	}
	return (count);
}


char ***get_piped_cmd_by_ptr(char **cmds, int *tokens)
{
    int num_of_cmds = 0;
    int i;
    int j;
    int flag;
    char ***cmd_ptr;
    //char** current_cmd = cmds;

    num_of_cmds = count_cmds(cmds, '|');
    cmd_ptr = malloc(sizeof(char **) * (num_of_cmds + 1));
    //cmd_ptr[num_of_cmds] = NULL;
    //(void)cmd_ptr;
    i = 0;
    flag = 0;
    j = 0;
    while (cmds && cmds[i] != NULL)
    {
        if (tokens[i] != 6 && flag == 0)
        {
            cmd_ptr[j] = &cmds[i];
            flag = 1;
            j++;
        }
        else if (tokens[i] == 6 && flag == 1)
        {
            flag = 0;
            free(cmds[i]);
            cmds[i] = NULL;
            //j++;
        }
        //printf("%d\t%s\n", tokens[i], cmds[i]);
        i++;
    }
    cmd_ptr[j] = NULL;
    return (cmd_ptr);
}

char	*ft_strdup_sep(char *s, char sep)
{
	char	*ret;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[n] && (s[n] != sep))
		n++;
	ret = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_strichr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*path_join(char *dir, char *cmd)
{
	char	*ret;
	int		total_lens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	total_lens = ft_strlen(dir) + ft_strlen(cmd);
	ret = malloc(sizeof(char) * (total_lens + 2));
	while (dir[i])
	{
		ret[j] = dir[i];
		j++;
		i++;
	}
	ret[j++] = '/';
	i = 0;
	while (cmd[i])
	{
		ret[j] = cmd[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (cmd);
	path = env[i] + 5;
	while (path && ft_strichr(path, ':') > -1)
	{
		dir = ft_strdup_sep(path, ':');
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (cmd);
}

void    exec_cmd(char **cmd_args, char **env)
{
    char    *path;
    
    if (ft_strichr(cmd_args[0], '/') > -1)
        path = cmd_args[0];
    else
        path = get_cmd_path(cmd_args[0], env);
    execve(path, cmd_args, env);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd_args[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    exit(127);
    //error_notcmd(cmd);
}

void    piping(char **cmd, int infile, int outfile, char **env, int *token, t_env *env_list) // t_env env_list
{
    int fd[2];
    int pid;
    int status;
    (void)env;

    pipe(fd);
    pid = fork(); // handle fork perror 
    if (pid == 0)
    {
        dup2(fd[1], outfile);
        close(fd[0]);
        close(fd[1]);
        if (ft_strncmp(cmd[0], "echo", 4) == 0 && !cmd[0][4])
        {
            printf("echo [piping] ============\n");
            delete_quoate(cmd);
            echo_cmd(cmd, token);
            exit(0); // the exit of echo, pwd, export, unset, ect ..
        }
        else if (ft_strncmp(cmd[0], "pwd" , 3) == 0 && !cmd[0][3])
        {
            printf("pwd [piping] ============\n");
            pwd_cmd(cmd);
            printf("zobiuat\n");
            exit(0); // the exit of echo, pwd, export, unset, ect ..
        }
        else if (ft_strncmp(cmd[0], "env", 3) == 0 && !cmd[0][3])
        {
            printf("env [piping] ============\n");
            env_cmd(cmd, env_list);
            exit(0); // the exit of echo, pwd, export, unset, ect ..
        }
        else if (ft_strncmp(cmd[0], "cd", 2) == 0 && !cmd[0][2])
        {
            printf("cd [piping] ============\n");
            cd_cmd(cmd, env_list);
            exit(0); // the exit of echo, pwd, export, unset, ect ..
        }
        else if (ft_strncmp(cmd[0], "export", 6) == 0)
        {
            printf("export [piping] ============\n");
            export_cmd(cmd, env_list);
            exit(0); // the exit of echo, pwd, export, unset, ect ..
        }
        else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        {
            printf("unset [piping] ============\n");
            unset_cmd(cmd, env_list);
            exit(0); // the exit of echo, pwd, export, unset, ect ..
        }
        else
            exec_cmd(cmd, env);
    }
    dup2(fd[0], infile);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        global_exit = WEXITSTATUS(status);
        //printf("Child process exited with status: %d\n", global_exit);
        // Handle exit status as needed
    }
    else
    {
        //printf("Child process terminated abnormally\n");
        // Handle abnormal termination as needed
    }
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char    *line;
    t_env   *env_list;
    if (ac > 1)
    {
        ft_putstr_fd("Error: too many arguments\n", 2);
        return (127);
    }
    env_list = create_env_list(env);
    line = readline(GREEN"minishell ▸ "WHITE);
    int walid = 1;
    //global_exit = 0;
    while (1)
    {
        if (line)
            add_history(line);
        else
            return (0); // handle ctrl + d
        if (parse(line))
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("Fork error");
                exit(1);
            }
            else if (pid == 0) // cmd
            {
                (void)env_list;
                char **parsed_line_args;
                int num_of_cmds;
                int *args_tokens;
                char ***cmd;
                int i;
                int out_fd = STDOUT;
                int stdout_copy = dup(STDOUT);
                int stdin_copy = dup(STDIN);
                (void)stdin_copy;
                
                line = parse_operator(line);
                parsed_line_args = args_split(line);
                num_of_cmds = count_cmds(parsed_line_args, '|');
                args_tokens = tokenise_cmd(parsed_line_args);
                if (walid == 1)
                {
                    printf("hdfdsjkfjksdfkjs\n");
                    expand(parsed_line_args, args_tokens, env_list);  // !!!!!
                }
                expand(parsed_line_args, args_tokens, env_list);
                cmd = get_piped_cmd_by_ptr(parsed_line_args, args_tokens);
                i = 0;
                while (i < num_of_cmds - 1)
                {
                    out_fd = STDOUT;
                    //
                    piping(cmd[i], STDIN, out_fd, env, args_tokens, env_list);
                    i++;
                }
                dup2(stdout_copy, STDOUT);
                exec_cmd(cmd[i], env);
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(cmd[i][0], 2);
                ft_putstr_fd(": command not found\n", 2);
                global_exit = 127;
                exit(127);
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
                // Handle child process exit status if needed
            }
            // builtins here to be affected by parent process
            /*==================================================================================================================*/
                char **parsed_line_args;
                int *args_tokens;
                int i = 0;
                char ***cmd;
                    
                line = parse_operator(line);
                parsed_line_args = args_split(line);
                args_tokens = tokenise_cmd(parsed_line_args);
                expand(parsed_line_args, args_tokens, env_list);
                cmd = get_piped_cmd_by_ptr(parsed_line_args, args_tokens);
            if (ft_strncmp(cmd[i][0], "echo", 4) == 0 && !cmd[i][0][4])
            {
                delete_quoate(cmd[i]);
                printf("zobiuat tq3 echo\n");
                echo_cmd(cmd[i], args_tokens);
            }
            else if (ft_strncmp(cmd[i][0], "pwd" , 3) == 0 && !cmd[i][0][3])
            {
                printf("pwd [while] ============\n");
                char	*cwd;
	            cwd = getcwd(NULL, 0);
                printf("pwd is =>%s", cwd);
	            if (!cwd)
                {
                    if (errno == ENOMEM)
                        ft_putstr_fd("pwd: out of memory\n", 2);
                    else if (errno == ERANGE)
                        ft_putstr_fd("pwd: path name too long\n", 2);
                    else
                        perror("pwd: getcwd error");
                }
	            ft_putendl_fd(cwd, 1);
	             free(cwd);
                //pwd_cmd(cmd[i]);
            }
            else if (ft_strncmp(cmd[i][0], "echo", 4) == 0 && !cmd[i][0][4])
            {
                delete_quoate(cmd[i]);
                echo_cmd(cmd[i], args_tokens);
            }
            else if (ft_strncmp(cmd[i][0], "env", 3) == 0 && !cmd[i][0][3])
            {
                env_cmd(cmd[i], env_list);
            }
            else if (ft_strncmp(cmd[i][0], "cd", 2) == 0 && !cmd[i][0][2])
            {
                printf("cd [while] ============\n");
                int ret = chdir("./libft");
                if (ret < 0)
                    printf("hhhhhhhhhhhhhhhhhhhhhhhhh\n");
                else
                    printf("yesssssssssssssss\n");
                //cd_cmd(cmd[i], env_list);
            }
            else if (ft_strncmp(cmd[i][0], "export", 6) == 0)
            {
                printf("export ============\n");
                export_cmd(cmd[i], env_list);
            }
            else if (ft_strncmp(cmd[i][0], "unset", 5) == 0)
            {
                printf("unset ============\n");
                unset_cmd(cmd[i], env_list);
            }
            else
            {
                printf("zobiuat else\n");
                exec_cmd(cmd[i], env);
            }
/*==================================================================================================================*/
        }
        walid++;
        line = readline(GREEN"minishell ▸ "WHITE);
    }
    return (global_exit);
}
