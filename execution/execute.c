/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 02:31:09 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 02:39:00 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute(char *line, t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
    pid_t pid = fork();
    check_fork_fail(&pid);
    init_cmd_data(cmd_data, line);
    if (pid == 0)
    {
        if (cmd_data->num_of_cmds > 1)
            multi_pipes_execution(cmd_data, redirection, env, env_list);
        if (cmd_data->num_of_cmds == 1)
            single_cmd_execution(cmd_data, redirection, env, env_list);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}
