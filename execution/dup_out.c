/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:48:14 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/25 01:47:03 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    establish_io_stream(char **cmd, int *cmd_tokens, t_redirection *redirection) // init output stream + duping
{
    establish_output_stream(cmd, cmd_tokens, redirection); // init output stream + duping
    establish_input_stream(cmd, cmd_tokens, redirection);
}

void    dup_io_before_piping(t_redirection *redirection)
{
    dup_output_before_piping(redirection);
	dup_input_before_piping(redirection);
}




void	dup_output_before_piping(t_redirection *redirection)
{
	if (redirection->out_fd != STDOUT)
		dup2(redirection->out_fd, STDOUT);
	else
		redirection->out_fd = STDOUT;
}

void	dup_output_after_piping(t_redirection *redirection)
{
	if (redirection->out_fd != STDOUT)
		redirection->out_fd = STDOUT;
}

void    dup_input_before_piping(t_redirection *redirection)
{
        if (redirection->in_fd != STDIN)
                dup2(redirection->in_fd, STDIN);
        else
                redirection->in_fd = STDIN;
}

void    dup_input_after_piping(t_redirection *redirection)
{
        if (redirection->in_fd != STDIN)
        {
                redirection->in_fd = STDIN;
        }
}


