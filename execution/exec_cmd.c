/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:21:15 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/21 17:35:07 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_join(char *dir, char *cmd)
{
	char	*ret;
	int		total_lens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	total_lens = ft_strlen(dir) + ft_strlen(cmd);
	ret = malloc(sizeof(char) * (total_lens + 2));
	while (dir[i])
	{
		ret[j] = dir[i];
		j++;
		i++;
	}
	ret[j++] = '/';
	i = 0;
	while (cmd[i])
	{
		ret[j] = cmd[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == NULL)
		return (cmd);
	path = env[i] + 5;
	while (path && ft_strichr(path, ':') > -1)
	{
		dir = ft_strdup_sep(path, ':');
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (cmd);
}

void    exec_cmd(char **cmd_args, char **env)
{
    char    *path;
    
    if (ft_strichr(cmd_args[0], '/') > -1)
        path = cmd_args[0];
    else
        path = get_cmd_path(cmd_args[0], env);
    execve(path, cmd_args, env);
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd_args[0], 2);
    ft_putstr_fd(": command not found\n", 2);
    exit(127);
    //error_notcmd(cmd);
}
