/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:21:15 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 21:24:19 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h> // for errno, ENOMEM, ERANGE

void	pwd_cmd(char **line)
{
	(void)line;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
    {
        if (errno == ENOMEM)
            ft_putstr_fd("pwd: out of memory\n", 2);
        else if (errno == ERANGE)
            ft_putstr_fd("pwd: path name too long\n", 2);
        else
            perror("pwd: getcwd error");
        return ;
    }
	ft_putendl_fd(cwd, 1);
	free(cwd);
}
