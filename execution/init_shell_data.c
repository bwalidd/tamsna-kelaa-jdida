/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:17:57 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 00:47:34 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd_data(t_cmd_data *cmd_data, char *line)
{
	line = parse_operator(line);
	cmd_data->parsed_line_args = args_split(line);
	cmd_data->num_of_cmds = count_cmds(cmd_data->parsed_line_args, '|');;
	cmd_data->args_tokens = tokenise_cmd(cmd_data->parsed_line_args);;
	cmd_data->cmd = get_piped_cmd_by_ptr(cmd_data->parsed_line_args, cmd_data->args_tokens);
	cmd_data->stdout_copy = dup(STDOUT);;
	cmd_data->stdin_copy = dup(STDIN);
	cmd_data->i = 0;
	(void)cmd_data->stdin_copy;
}
