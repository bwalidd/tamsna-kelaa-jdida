/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:40:27 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 15:58:06 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
┌──(toowan㉿toowan)-[~]
└─$ unset LS_COLOR*                     
unset: LS_COLOR*: invalid parameter name
*/


void    unset_cmd(char **cmd, t_env *env_list)
{
    int     i;
    int     cmd_len;
    int     env_len;
    int     n;
    t_env   *env_header;

    env_header = env_list;
    i = 1;
    while (cmd[i])
    {
        env_list = env_header;
        cmd_len = ft_strlen(cmd[i]);
        while (env_list != NULL)
        {
            env_len = ft_strlen(env_list->env_name);
            if (env_len > cmd_len)
                n = env_len;
            else
                n = cmd_len;
            if ((ft_strncmp(cmd[i], env_list->env_name, n) == 0) && env_list->unset != 1)
            {
                env_list->unset = 1;
                break ;
            }
            else
            env_list = env_list->next;
        }
        i++;
    }
    return ;
}