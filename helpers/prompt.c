/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:34:37 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/25 21:59:35 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void    get_user_input(t_env *env_list)
{
	t_env *tmp;
	
	tmp = ft_envlst_search(env_list, "USER");
	if(!tmp)
	{
		printf(": ");
		return ;
	}
	else
	{
		printf(BLUE"%s: "WHITE, tmp->env_value);
	}
	free(tmp);
}

void   get_path(t_env *env_list)
{
	t_env	*tmp;
	char	*path;
	int     tmp_len;
	char	*printer;

	
	path = getcwd(NULL, 0);
	tmp = ft_envlst_search(env_list, "HOME");
	if(tmp && ft_envlst_len(tmp) > 0)
	{
		tmp_len = ft_strlenn(tmp->env_value);
		if(ft_strncmp(path, tmp->env_value, tmp_len) == 0)
		{
			printer = ft_substr(path, tmp_len, ft_strlenn(path) - tmp_len);
			printf(BLUE"[~%s: ]"WHITE, printer);
			free(printer);
			free(path);
			return ;
		}   
	}
	printf(BLUE"[%s: ]"WHITE, path);
	free(path);
}

void    prompt(t_env *env_list)
{
	get_user_input(env_list);
	get_path(env_list);
}
