/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:49:31 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 16:21:07 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    env_cmd(char **cmd, t_env *env_list)
{
    (void)cmd;
    while (env_list != NULL)
    {
        if (env_list->unset != 1)
        {
            ft_putstr_fd(env_list->env_name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(env_list->env_value, 1);
            ft_putstr_fd("\n", 1);
        }
        env_list = env_list->next;
    }
}
