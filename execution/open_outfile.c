/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:47:13 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 04:53:26 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_redirect_to_null(char **cmd, int *cmd_tokens)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_tokens[i] == 4 || cmd_tokens[i] == 7) // || cmd_tokens[i] == 0 || cmd_tokens[i] == 0
			cmd[i] = NULL;
		i++;
	}
}

int		get_redirection_index(int *cmd_tokens, t_redirection *redirection)
{
	int	i;

	i = 0;
	while (cmd_tokens[i])
    {
        if (cmd_tokens[i] == 4 || cmd_tokens[i] == 7)
        {
            redirection->redirection_token = cmd_tokens[i];
			return (i);
        }
        i++;
    }
	return (0); // return ;
}

int		get_outfile_index(int *cmd_tokens, int index)
{
	while (cmd_tokens[index])
	{
		if (cmd_tokens[index] == 5 || cmd_tokens[index] == 8)  //// !!! may be
        {
            return (index);
        }
		index++;
	}
	return (0); // return ;
}

void	establish_output_stream(char **cmd, int *cmd_tokens, t_redirection *redirection)
{
	redirection->redirection_token = 0;
	redirection->redirection_index = 0;
	redirection->outfile_index = 0;
	//redirection->outfile = 
	redirection->out_fd = STDOUT;

	redirection->redirection_index = get_redirection_index(cmd_tokens, redirection);
	redirection->outfile_index = get_outfile_index(cmd_tokens, redirection->redirection_index);
	redirection->outfile = cmd[redirection->outfile_index];
	if (redirection->redirection_index != 0 && redirection->outfile_index != 0)
	{
		if (redirection->redirection_token == 4)
			redirection->out_fd = open(redirection->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else if (redirection->redirection_token == 7)
			redirection->out_fd = open(redirection->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (redirection->out_fd == -1)
    	{
        	perror("Error opening output file");
        	exit(1);
    	}
	}
	set_redirect_to_null(cmd, cmd_tokens);
}
