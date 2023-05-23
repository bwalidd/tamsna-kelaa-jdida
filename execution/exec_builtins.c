/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:33:31 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 03:32:53 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     is_builtins(char *cmd)
{
    if (ft_strncmp(cmd, "echp", 4) == 0 && !cmd[4])
        return (1);
    if (ft_strncmp(cmd, "cd", 2) == 0 && !cmd[2])
        return (1);
    else if (ft_strncmp(cmd, "pwd" , 3) == 0 && !cmd[3])
        return (1);
    else if (ft_strncmp(cmd, "exit", 4) == 0 && !cmd[4])
        return (1);
    else if (ft_strncmp(cmd, "env", 3) == 0 && !cmd[3])
        return (1);
    else if (ft_strncmp(cmd, "export", 6) == 0 && !cmd[6])
        return (1);
    else if (ft_strncmp(cmd, "unset", 5) == 0 && !cmd[5])
        return (1);
    else
        return (0);
}

void     exec_builtins(char **cmd, int *tokens, t_env *env_list)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0 && !cmd[0][4])
    {
        echo_cmd(cmd, tokens); // provide env_list and token
    }
    else if (ft_strncmp(cmd[0], "cd", 2) == 0 && !cmd[0][2])
    {
        delete_quoate(cmd);
        cd_cmd(cmd, env_list);
    }
    else if (ft_strncmp(cmd[0], "pwd" , 3) == 0 && !cmd[0][3])
    {
        pwd_cmd(cmd);
    }
    else if (ft_strncmp(cmd[0], "exit", 4) == 0 && !cmd[0][4])
    {
        exit_cmd(cmd); // provide env_list
    }
    else if (ft_strncmp(cmd[0], "env", 3) == 0 && !cmd[0][3])
    {
        env_cmd(cmd, env_list);
    }
    else if (ft_strncmp(cmd[0], "export", 6) == 0 && !cmd[0][6])
    {
        export_cmd(cmd, env_list);
    }
    else if (ft_strncmp(cmd[0], "unset", 5) == 0 && !cmd[0][5])
    {
        unset_cmd(cmd, env_list);
    }
    // exit b returned int value here
}