/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:15 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/25 21:59:12 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char *replace_wrong_name(char *cmd, int *i)
{
    char    *str;
    char    *str2;

    str = ft_strdup(cmd);
    str[*i] = 0;
    str2 = ft_substr(cmd, (*i) + 2, ft_strlenn(str));
    free(cmd);
    cmd = ft_strjoin(str, str2);
    *i = ft_strlenn(str);
    free(str);
    free(str2);
    return (cmd);
}
/*
 echo "sisisissi"$*"dsssqwe"
 str = "sisisissi"
 str2 = "dsssqwe"
 cmd = "sisisissi"""dsssqwe"
*/
char    *replacing(char *cmd, int *i)
{
    char    *exit;
    char    *str;
    char    *str2;

    exit = ft_itoa(global_exit);
    str = ft_substr(cmd,0,*i);
    str2 = ft_strjoin(str,exit);
    free(exit);
    free(str);
    str = ft_substr(cmd, (*i) + 2, ft_strlenn(cmd));
    free(cmd);
    cmd = ft_strjoin(str2, str);
    *i = ft_strlenn(str2);
    free(str);
    free(str2);
    return (cmd);
}


/*
echo 
"hi my name is"$?"exit status"
"hi my name is"90"exit status"
*/

/*
str = "hi my name is"
str2 = "hi my name is"0
str = "exit status"
cmd = "hi my name is"0"exit status"
*/