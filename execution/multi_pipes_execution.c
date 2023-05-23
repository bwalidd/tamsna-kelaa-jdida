/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:21:10 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 01:28:22 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multi_pipes_execution(t_cmd_data *cmd_data, t_redirection *redirection, char **env, t_env *env_list)
{
	int	i;

	i = 0;
	while (i < cmd_data->num_of_cmds - 1)
    {
        cmd_data->cmd_tokens = tokenise_cmd(cmd_data->cmd[i]);
        establish_output_stream(cmd_data->cmd[i], cmd_data->cmd_tokens, redirection); // init output stream + duping
        dup_output_before_piping(redirection);
		piping(cmd_data->cmd[i], STDIN, redirection->out_fd, env, env_list, cmd_data->args_tokens);
        dup_output_after_piping(redirection);
		i++;
    }
    // latest cmd in the pipe here ..
    dup2(cmd_data->stdout_copy, STDOUT);
    exec_cmd(cmd_data->cmd[i], env);
    cmd_not_found(cmd_data->cmd[i][0], &global_exit);
}
