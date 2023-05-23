/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/23 01:34:40 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_exit;

int main(int ac, char **av, char **env)
{
    (void)av;
    char            *line;
    t_env           *env_list;
    t_redirection   *redirection;
    t_cmd_data *cmd_data;
    
    check_argc(ac);
    env_list = create_env_list(env);
    redirection = malloc(sizeof(t_redirection));
    cmd_data = malloc(sizeof(t_cmd_data) * 1);
    line = readline(GREEN"minishell ▸ "WHITE);
    global_exit = 0;
    while (1)
    {
        if (line)
            add_history(line);
        else
            return (0);
        if (parse(line))
        {
            pid_t pid = fork();
            check_fork_fail(&pid);
            init_cmd_data(cmd_data, line);
            if (pid == 0)
            {
                if (cmd_data->num_of_cmds > 1)
                    multi_pipes_execution(cmd_data, redirection, env, env_list);
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
            }
            // execute_only_cmd
            if (cmd_data->num_of_cmds == 1)
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
        }
        line = readline(GREEN"minishell ▸ "WHITE);
    }
    return (global_exit);
}
