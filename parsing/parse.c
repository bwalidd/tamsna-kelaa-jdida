/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:49:24 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/26 14:45:27 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

// check if is unclosed quotes
static int is_unclosed_quotes(char *line)
{
    int i;
    char quotes;

    i = 0;
    if (!ft_strchr(line, '\'') && !ft_strchr(line, '\"'))
        return (0);
    while (line[i])
    {
        quotes = 'x';
        if (line[i] == '\'' || line[i] == '\"')
        {
            quotes = line[i];
            i++;
            while (line[i])
            {
                if (line[i] == quotes)
                {
                    quotes = '0';
                    break;
                }
                i++;
            }
        }
        i++;
    }
    if (quotes != '0')
    {
        ft_putstr_fd("minishell: unclosed quotes\n", 2);
        return (1);
    }
    return (0);
}
// echo "hell'o" | wc

int parse(char *line)
{
	if (!line || !(*line))
	{
		global_exit = 2;
		return (0);
	}
	if (check_oper('|', line, 1) || check_oper('<', line, 2) || check_oper('>', line, 2))
	{
		global_exit = 2;
		return (0);
	}
	if (check_oper_in_last(line, '|') || check_oper_in_last(line, '<') || check_oper_in_last(line, '>'))
	{
		global_exit = 2;
		return (0);
	}
	if (check_chars(line,"\\;&") || check_pipe(line))
	{
		global_exit = 2;
		return (0);
	}
	if (is_empty(line) || is_unclosed_quotes(line))
	{
		global_exit = 2;
		return (0);
	}
	
	return (1);
}
