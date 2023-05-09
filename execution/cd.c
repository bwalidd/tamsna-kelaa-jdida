/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:23:19 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 16:21:41 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    cd_cmd(char **cmd, t_env *env_list)
{
    int     ret;
    char    *path;
    char    *pwd;
    char    **export_cwd;
    char    *tmp_arg;

    pwd = getcwd(NULL, 0);
    ret = 0;
    if (cmd[0] && !cmd[1])
        ret = chdir("/Users/oel-houm"); // $HOME
    else
    {
        path = ft_strdup(cmd[1]);
        ret = chdir(path);
    }
    (void)env_list;
    if (ret == -1) // if chdir() returns -1, it means that the directory could not be changed.
        perror("chdir error"); // using perror to print the error message to the console.
    else
    {
        if (pwd)
        {
            tmp_arg = ft_strjoin("export OLDPWD=", pwd);
            export_cwd = ft_split(tmp_arg, ' ');
            free(tmp_arg);
            export_cmd(export_cwd, env_list);
            free(export_cwd);
            free(pwd);
        }
        if ((pwd = getcwd(NULL, 0)))
        {
            tmp_arg = ft_strjoin("export PWD=", pwd);
            export_cwd = ft_split(tmp_arg, ' ');
            free(tmp_arg);
            export_cmd(export_cwd, env_list);
            free(export_cwd);
            free(pwd);
        }
    }
    // free(pwd);
    return ;
}