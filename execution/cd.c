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

/*
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
        // path = ft_strdup(cmd[1]);
        // ret = chdir(path);
        path = ft_strdup(cmd[1]);
        if (access(path, R_OK | X_OK) != 0)
        {
            perror("/ User does not have read/execute permission for directory");
        }
        if (access(path, F_OK) == -1) // Check if the directory exists
            perror("No such file or directory"); // If the directory does not exist, print an error message
        else if (access(path, X_OK) == -1) // Check if the directory is executable
            perror("Not a directory"); // If the directory is not executable, print an error message
        else
            ret = chdir(path); // If the directory exists and is executable, change the directory
        free(path);
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
*/

void cd_cmd(char **cmd, t_env *env_list)
{
    int ret;
    char *path;
    char *pwd;
    char **export_cwd;
    char *tmp_arg;

    pwd = getcwd(NULL, 0);
    ret = 0;
    if (cmd[0] && !cmd[1])
        ret = chdir("/Users/oel-houm"); // $HOME
    else
    {
        path = ft_strdup(cmd[1]);
        if (access(path, R_OK | X_OK) != 0)
        {
            perror("minishell: cd");
            //perror("Permission denied");
        }
        else if (access(path, F_OK) == -1)
        {
            perror("No such file or directory");
        }
        else if (access(path, X_OK) == -1)
        {
            perror("Not a directory");
        }
        else
        {
            ret = chdir(path);
        }
        free(path);
    }
    (void)env_list;
    if (ret == -1)
    {
        perror("chdir error");
    }
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
        pwd = getcwd(NULL, 0);
        if (pwd)
        {
            tmp_arg = ft_strjoin("export PWD=", pwd);
            export_cwd = ft_split(tmp_arg, ' ');
            free(tmp_arg);
            export_cmd(export_cwd, env_list);
            free(export_cwd);
            free(pwd);
        }
        else
        {
            perror("getcwd error");
        }
    }
    return;
}
