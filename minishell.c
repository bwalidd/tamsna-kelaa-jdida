/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/28 15:16:32 by oel-houm         ###   ########.fr       */
=======
/*   Updated: 2023/04/27 17:58:47 by wbouwach         ###   ########.fr       */
>>>>>>> 06dea568cd8f3cf4eb7dfa051c3e5c6b13304899
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_exit;

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
<<<<<<< HEAD
            //int i = 0;
            printf("%s\n", parse_operator(cmd));
            free(cmd);
            cmd = parse_operator(cmd);
            //char **s = args_split(cmd);
            //int *t = tokenise_cmd(s);
            //while(s && s[i] && t && t[i])
           // {
             //   printf("%s ===== %d\n",s[i],t[i]);
               // i++;
            //}
            
=======
            int i = 0;
            printf("%s\n", cmd);
            
            cmd = parse_operator(cmd);
            char **s = args_split(cmd);
            int *t = tokenise_cmd(s);
            while (s[i] && t[i])
            {
                printf("%s === %d\n", s[i], t[i]);
                i++;
            }
            //wgiuuggie
>>>>>>> 06dea568cd8f3cf4eb7dfa051c3e5c6b13304899
        }
       // prompt(env_list);
       free(cmd);
        cmd = readline(BLUE"MINISHELL$ "WHITE);
    }
    
    return (global_exit);
}
