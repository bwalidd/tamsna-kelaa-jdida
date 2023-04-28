/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:35 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/27 17:48:36 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int arg_len_counter(char *cmd)
{
    int i;
    int flag;

    flag = 0;
    i = 0;
    while (cmd && cmd[i])
    {
        if (cmd[i] == '\'' || cmd[i] == '"')
            quoate_flag(&flag,cmd[i]);
        i++;
        if (is_space(cmd[i]) && flag == 0)
            break;
    }
    return (i);
}


static int count_args(char *cmd)
{
    int i;
    int count;
    int flag;

    flag = 0;
    count = 0;
    i = 0;
    while (cmd && cmd[i])
    {
        if (cmd[i] == '\'' || cmd[i] == '\"')
            quoate_flag(&flag,cmd[i]);
        i++;
        if (is_space(cmd[i]) && flag == 0)
        {
            while (cmd[i] && is_space(cmd[i]))
                i++;
            if (cmd[i])
                count++;
        }
    }
    return (count + (flag == 0));
    //echo "'hello' there" == 2
    //echo 'hello' there == 3
}

char    **args_split(char *cmd)
{
    char    **split;
    int     nb_args;
    int     arg_len;
    int     i;

    while (cmd && *cmd && is_space(*cmd))
        cmd++;
    nb_args = count_args(cmd);
    split = malloc((nb_args + 1) * sizeof(char *));
    split[nb_args] = NULL;
    i = 0;
    while (i < nb_args)
    {
       arg_len = arg_len_counter(cmd);
       split[i] = ft_substr(cmd, 0, arg_len); 
       cmd += arg_len;
       while (*cmd && is_space(*cmd))
            cmd++;
        i++;
    }
    return (split);
}