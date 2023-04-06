/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:52:46 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/06 23:52:47 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirection(char c)
{
    if (c == '<' || c == '>')
        return (1);
    return (0);
}

int is_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int	ft_array_size(char **array_str)
{
	int	i;

	i = 0;
	while (array_str && array_str[i])
		i++;
	return (i);
}