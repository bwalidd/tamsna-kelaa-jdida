/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:21:15 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 16:19:16 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_cmd(char **line)
{
	(void)line;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("getcwd"); //manage the error
	ft_putendl_fd(cwd, 1);
	free(cwd);
}