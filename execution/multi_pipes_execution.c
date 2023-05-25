/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:21:10 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/25 01:46:25 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multi_pipes_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
    pid_t pid;
            
                pid = fork();
                check_fork_fail(&pid);
                if (pid == 0)
                {
                    int i = 0;
                    while (i < cmd_data->num_of_cmds - 1)
                    {
                        int *cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
                        establish_io_stream(cmd_data->cmd[i], cmd_tokens, redirection); // init output stream + duping
                	    dup_io_before_piping(redirection);
                        piping(cmd_data->cmd[i], STDIN, redirection->out_fd, env, env_list, cmd_data->args_tokens);
                        dup_output_after_piping(redirection);
                        i++;
                    }
                    int *cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
                    establish_io_stream(cmd_data->cmd[i], cmd_tokens, redirection); // init output stream + duping
                    if (redirection->out_redirection_token == 0)
                            redirection->out_fd = cmd_data->stdout_copy;
                    else
                        redirection->out_fd = open(redirection->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
                    dup_output_before_piping(redirection);
	                dup_input_before_piping(redirection);
                    exec_cmd(cmd_data->cmd[i], env);
                    cmd_not_found(cmd_data->cmd[i][0], &global_exit);
                }
                else
                {
                    int status;
                    waitpid(pid, &status, 0);
                    // Handle child process exit status if needed
                }
}
// pwd | cat > out | ls > lolo
// if outfile == null then redirect to outfile stdout

// pwd | < minishell.c head | wc > lolo | ls > popo
//                       -> ! ->
// head minishell.c | < Makefile  head | wc > here | cat
// head minishell.c | cat | cat | cat > haha | ls
