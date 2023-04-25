/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:21:42 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/07 02:44:13 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *ft_envlst_new(char *str)
{
    t_env *new;

    new = ft_calloc(sizeof(t_env), 1);
    if (!new)
        return (0);
    if(!ft_strchr(str, '='))
    {
        new->env_name = ft_strdup(str);
        if (!new->env_name)
            return (0);
        new->env_value = NULL;
    }
    else
    {
        new->env_name = ft_substr(str, 0, ft_strchr(str, '=') - str);
        if (!new->env_name)
            return (0);
        new->env_value = ft_strdup(ft_strchr(str, '=') + 1);
        if (!new->env_value)
            return (0);
    }
    return (new);
}

t_env	*ft_envlst_search(t_env *env, char *searched)
{
	t_env	*new;

	new = env;
	while (new != NULL)
	{
		if (!ft_strcmp(new->env_name, searched))
			return (new);
		new = new->next;
	}
	return (NULL);
}

void    ft_envlst_add_back(t_env **head, t_env *new)
{
    t_env *tmp;

    tmp = *head;
    if (!tmp)
    {
        *head = new;
        return ;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}

t_env   *create_env_list(char **env)
{
    t_env *new;
    t_env *head;
    int i;
    
    i = 0;
    head = NULL;
    while (env[i])
    {
        new = ft_envlst_new(env[i]);
        ft_envlst_add_back(&head, new);
        i++;
    }
    return (head);
}