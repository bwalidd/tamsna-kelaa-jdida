/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:23:19 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 15:56:42 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    cd_cmd(char **cmd, t_env *env_list)
{
    //if (**char args && args[1] && args[2])
    // then print "error: too many arguments" + exit(1)
    // printf("d=%d\n", find_env(cmd[1], env_list));
    // cd ./project313/42network
    // add in $OLDPWD and $PWD

    // KAYN WA7D LPROBLEM MNIN KANDIR UNSET PATH, PWD, OLDPWD
        // khassni nzid export PWD=$PATH instead of dak tkhrbi9 li dayr 
    int     ret;
    char    *path;
    char    *pwd;
    char    **export_cwd;
    char    *tmp_arg;

    pwd = getcwd(NULL, 0);
    ret = 0;
    if (cmd[0] && !cmd[1])
        ret = chdir("/Users/oel-houm");
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
        // ft_putstr_fd("PWD=", 1);
        // ft_putstr_fd(get_env_value("PWD", env_list), 1);  // and env_list->unset == 0 (to add)
        // ft_putstr_fd("\n", 1);
        // ft_putstr_fd("OLDPWD=", 1);
        // ft_putstr_fd(get_env_value("OLDPWD", env_list), 1);  // and env_list->unset == 0
        // ft_putstr_fd("\n", 1);
    }
    // free(pwd);
    return ;
}