/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:40:53 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/20 05:41:36 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     check_n_sequence(char *str)
{
    int i;

    i = 0;
    if (str[i] != '-')
        return (0);
    i++;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void   echo_cmd(char **line, int *t) // remove the flag_ #FIX
{
    int i;
    int j;
    int jlen;
    int flag_n;
    int flag_ = 0;

    i = 0;
    flag_n = 0;
    while (line[i])
    {
        if (t[i] == 2)
        {
            j = 0;
            jlen = ft_strlen(line[i]) - 1;
            if ((ft_strncmp(line[i], "-n", 2) == 0 || check_n_sequence(line[i]) == 1) && flag_ == 0)
            {
                if (check_n_sequence(line[i]) == 0)
                {
                    int j;

                    j = 0;
                    while (line[i][j])
                    {
                        write(1, &line[i][j], 1);
                        j++;
                    }
                    if (line[i + 1] != NULL)
                        write(1, " ", 1);
                    flag_n = 0;
                }
                else
                    flag_n = 1;
            }
            else
            {
                flag_ = 1;
                j = 0;
                while (j < jlen + 1)
                {
                    write(1, &line[i][j], 1);
                    j++;
                }
                if (line[i + 1] != NULL)
                {
                    write(1, " ", 1);
                }
            }
            
        }
        i++;
    }
    if (flag_n == 0)
        write(1, "\n", 1);
 }