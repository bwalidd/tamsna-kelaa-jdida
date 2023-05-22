/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_out.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:48:14 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/21 23:11:21 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
