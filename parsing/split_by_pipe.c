/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:44:51 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/21 17:45:14 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char ***get_piped_cmd_by_ptr(char **cmds, int *tokens)
{
    int num_of_cmds = 0;
    int i;
    int j;
    int flag;
    char ***cmd_ptr;

    num_of_cmds = count_cmds(cmds, '|');
    cmd_ptr = malloc(sizeof(char **) * (num_of_cmds + 1));
    i = 0;
    flag = 0;
    j = 0;
    while (cmds && cmds[i] != NULL)
    {
        if (tokens[i] != 6 && flag == 0)
        {
            cmd_ptr[j] = &cmds[i];
            flag = 1;
            j++;
        }
        else if (tokens[i] == 6 && flag == 1)
        {
            flag = 0;
            free(cmds[i]);
            cmds[i] = NULL;
        }
        i++;
    }
    cmd_ptr[j] = NULL;
    return (cmd_ptr);
}
