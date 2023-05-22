/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:40:27 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 21:09:59 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void    print_export_string(char *str)
{
    int     i;

    i = 0;
    while (str[i] != '\0')
    {
        write(2, &str[i], 1);
        i++;
    }
}

static void    print_invalid_identifier_error(char *str)
{
    ft_putstr_fd("minishell: unset: `", 2);
    print_export_string(str);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

static int     is_allowed_2(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] >= 33 && str[i] <= 47) ||
            (str[i] >= 58 && str[i] <= 64) ||
            (str[i] >= 91 && str[i] <= 94) ||
            (str[i] == 96) ||
            (str[i] >= 123 && str[i] <= 126))
            return (0);
        i++;
    }
    return (1);
}    

void    unset_cmd(char **cmd, t_env *env_list)
{
    int     i;
    int     cmd_len;
    int     env_len;
    int     n;
    t_env   *env_header;

    env_header = env_list;
    i = 1;
    while (cmd[i])
    {
        if (is_allowed_2(cmd[i]) == 0)
            print_invalid_identifier_error(cmd[i]);
        else
        {
            env_list = env_header;
            cmd_len = ft_strlen(cmd[i]);
            while (env_list != NULL)
            {
                env_len = ft_strlen(env_list->env_name);
                if (env_len > cmd_len)
                    n = env_len;
                else
                    n = cmd_len;
                if ((ft_strncmp(cmd[i], env_list->env_name, n) == 0) && env_list->unset != 1)
                {
                    env_list->unset = 1;
                    break ;
                }
                else
                env_list = env_list->next;
            }
        }
        i++;
    }
    return ;
}