/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_oper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:52:59 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/06 23:53:00 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quoate_flag(int *flag, int c)
{
	if (c == '\'')
	{
		if (*flag == 1)
			*flag = 0;
		else if (*flag == 0)
			*flag = 1;
	}
	if (c == '\"')
	{
		if (*flag == 2)
			*flag = 0;
		else if (*flag == 0)
			*flag = 2;
	}
}

int check_oper(char c, char *line, int nb)
{
    int	i;
	int flag;
	int cmpt;

	i = 0;
	flag = 0;
	while (line[i])
	{
		quoate_flag(&flag, line[i]);
		cmpt = 0;
		while (line[i] == c && flag == 0 && line[i])
		{
			cmpt++;
			i++;
			quoate_flag(&flag, line[i]);
		}
		if(flag == 0 && cmpt > nb)
		{
			write(2,"syntax error\n",13);
			return (1);
		}
		if(line[i] == NULL)
			break;
	}
	return (0);
}
