/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:03 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/14 23:30:08 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_pipe(char *line)
{
    if (*line == '|')
    {
        ft_putstr_fd("syntax error near unexpected token `|'\n",2);
        return (1);
    }
    return (0);
}

// check that << and >> and | in the last of cmd
int check_oper_in_last(char *line ,char c)
{
    int i;

    i = 0;
    while (line[i] != '\0')
        i++;
    i--;
    while(line[i] == ' ' || line[i] == '\t')
        i--;
    if (line[i] == c)
    {
        printf("syntax error near unexpected token `newline'\n");
        return (1);
    }
    return (0);   
}