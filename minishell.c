/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/09 16:15:11 by oel-houm         ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
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
