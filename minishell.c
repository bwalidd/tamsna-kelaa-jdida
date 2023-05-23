/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/23 04:31:32 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_exit;

int main(int ac, char **av, char **env)
{
    // initiate_values(T_DATA);
    char            *line;
    t_env           *env_list;
    t_redirection   *redirection;
    t_cmd_data      *cmd_data;
    
    (void)av;
    check_argc(ac);
    global_exit = 0;
    env_list = create_env_list(env);
    redirection = malloc(sizeof(t_redirection));
    cmd_data = malloc(sizeof(t_cmd_data));
    line = readline(GREEN"minishell ▸ "WHITE);
    while (1)
    {
        if (line)
            add_history(line);
        else
        {
            write(1, "\n", 1);
        }
        if (parse(line))
            execute(line, cmd_data, redirection, env, env_list);
        line = readline(GREEN"minishell ▸ "WHITE);
    }
    return (global_exit);
}
