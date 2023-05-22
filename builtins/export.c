/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:53:43 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/09 21:09:12 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* this function need some improvements (to fix later):
ft_strdup(char *str, char limiter, )
*/
void    do_export(char *str, t_env *env_list)
{
    int var_len;
    int value_len;
    int flag;
    int i;

    i = 0;
    flag = 0;
    var_len = 0;
    value_len = 0;
    while (str[i])
    {
        if (str[i] == '=')
            break ;
        i++;
    }
    var_len = i;
    if (str[i] == '=' && str[i + 1])
    {
        flag++;
        i++;
    }
    while (str[i])
    {
        value_len++;
        i++;
    }
    char *var = malloc(sizeof(char) * var_len + 1 );
    char *val = malloc(sizeof(char) * value_len + 1);
    i = 0;
    while (i < var_len)
    {
        var[i] = str[i];
        i++;
    }
    var[i] = '\0';
    i = 0;
    str = &str[var_len + 1];
    while (*str)
    {
        val[i] = *str;
        i++;
        str++;
    }
    val[i] = '\0';

    t_env   *tail_env;
    while (env_list != NULL)
    {
        if (env_list->next == NULL)
            tail_env = env_list;
        if (ft_strncmp(env_list->env_name, var, var_len) == 0)
            env_list->unset = 1;
        env_list = env_list->next;
    }

    t_env   *new_env;
    new_env = malloc(sizeof(t_env));
    new_env->env_name = var;
    new_env->env_value = val;
    new_env->unset = 0;

    new_env->prev = tail_env;
    new_env->next = NULL;
    tail_env->next = new_env;
}

static void    print_export_string(char *str)
{
    int     i;

    i = 0;
    while (str[i] != '=' && str[i] != '\0')
    {
        write(2, &str[i], 1);
        i++;
    }
}


static void    print_invalid_identifier_error(char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    print_export_string(str);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

int     is_allowed(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != '=')
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

int is_nospace(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (0);
        i++;
    }
    return (1);
}

// allowed begin char
void     if_allowed(char *str, t_env *env_list) // export_checker //check begin // check export arg
{
    int i;

    i = 1;
    if (!ft_isalpha(str[0]) && str[0] != '_')         // check begining str[0]
    {
        while (str[i] != '\0' && str[i] != '=')
        {
            if (str[0] >= 48 && str[0] <= 57)
            {
                print_invalid_identifier_error(str);
                return ;
            }
            else if ((str[0] >= 33 && str[0] <= 47) ||
                (str[0] >= 58 && str[0] <= 64) ||
                (str[0] >= 91 && str[0] <= 96) ||
                (str[0] >= 123 && str[0] <= 126))
            {
                print_invalid_identifier_error(str);
                return ;
            }
            i++;
        }
    }
    else //check all str
    {
        if (is_nospace(&str[i]) == 1)
            return ;
        else if (is_allowed(&str[i]) == 1)
            do_export(str, env_list);
        else
            print_invalid_identifier_error(str);
    }
    return ;
}

void    export_cmd(char **cmd, t_env *env_list)
{
    int i;
    i = 1;
    if (cmd[0] && !cmd[1])
    {
        while (env_list)
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(env_list->env_name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(env_list->env_value, 1);
            ft_putstr_fd("\n", 1);
            env_list = env_list->next;
        }
    }
    else
    {
        while (cmd[i])
        {
            if_allowed(cmd[i], env_list);
            i++;
        }
    }
    return ;
}