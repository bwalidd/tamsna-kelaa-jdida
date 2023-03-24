/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/03/23 02:52:21 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *cmd;
    t_env *env_list;
    (void)av;
    if (ac > 1)
    {
        printf("Error: too many arguments\n");
        return (1);
    }
    env_list = create_env_list(env);
    prompt(env_list);
    cmd = readline("$ ");
    while (cmd)
    {
        if (*cmd)
            add_history(cmd);
        if (ft_strncmp(cmd, "exit", 4) == 0)
            exit(0);
        if (parse(line))
            
    }
}