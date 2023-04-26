/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/26 21:20:59 by wbouwach         ###   ########.fr       */
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
            int i = 0;
            printf("%s\n", parse_operator(cmd));
            free(cmd);
            cmd = parse_operator(cmd);
            char **s = args_split(cmd);
            int *t = tokenise_cmd(s);
            while(s && s[i] && t && t[i])
            {
                printf("%s ===== %d\n",s[i],t[i]);
                i++;
            }
            
        }
       // prompt(env_list);
       free(cmd);
        cmd = readline(BLUE"MINISHELL$ "WHITE);
    }

    
   
    
    return (global_exit);
}