/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unsupport.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:06 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/07 17:09:39 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_unsupport(char *line)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (line[i])
    {
        quoate_flag(&flag,line[i]);
        if((line[i] == '>' && flag == 0) || (flag == 0 && line[i] == '<'))
        {
            if ((line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '<' && line[i + 1] == '>'))
			{
                write(2,"syntax error\n",13);
                return (1);
            }
        }
        i++;
    }
    return (0);
}