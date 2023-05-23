/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:21:42 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 01:45:31 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    single_cmd_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
    cmd_data->cmd_tokens = tokenise_cmd(cmd_data->cmd[0]);
    establish_output_stream(cmd_data->cmd[0], cmd_data->cmd_tokens, redirection);
    if (is_builtins(cmd_data->cmd[0][0]) == 1)
    {
        int pid = fork();
        if (pid == 0)
        {
            dup2(redirection->out_fd, STDOUT);
            exec_builtins(cmd_data->cmd[0], cmd_data->args_tokens, env_list);
            exit(0);
        }
        else if (pid > 0)
            wait(&pid);
    }
    else
    {
        int pid = fork();
        if (pid == 0)
        {
            dup2(redirection->out_fd, STDOUT);
            exec_cmd(cmd_data->cmd[0], env);
        }
        else if (pid > 0)
            wait(&pid);
    }
}
