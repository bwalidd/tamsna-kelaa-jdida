/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:23:19 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/23 03:33:28 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2); // remove had la9lawi
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static void update_PWD_and_OLDPWD(char *pwd, t_env *env_list)
{
    char    **export_cwd;
    char    *tmp_arg;

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
        perror("minishell: getcwd");
}

void cd_cmd(char **cmd, t_env *env_list)
{
    int     cd_ret;
    char    *path;
    char    *pwd;

    cd_ret = 0;
    pwd = getcwd(NULL, 0);
    if (cmd[0] && !cmd[1])
    {
        path = ft_strdup("/Users/oel-houm");
        //path = ft_strdup("/home/toowan");
        if (access(path, F_OK) != -1)
            cd_ret = chdir(path); // $HOME
        else
            perror("minishell: cd");
        free(path);
    }
    else
    {
        path = ft_strdup(cmd[1]);
        cd_ret = chdir(path);
        free(path);
        if (cd_ret < 0)
            cd_ret *= -1;
        if (cd_ret != 0)
            print_error(cmd);
        else
            update_PWD_and_OLDPWD(pwd, env_list);
    }
    return;
}
