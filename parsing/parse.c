/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 02:49:24 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/07 17:06:08 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_empty(char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '\t')
            return (0);
        line++;
    }
    return (1);
}


int is_unclosed_quotes(char *line)
{
    int i;
    int single_quotes;
    int double_quotes;

    i = 0;
    double_quotes = 0;
    single_quotes = 0;
    while (line[i])
    {
        if (line[i] == '"')
            double_quotes++;
        else if (line[i] == '\'')
            single_quotes++;
        i++;
    }
    if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
    {
        printf("Error: unclosed quotes\n");
        return (1);
    }
    return (0);
}


int parse(char *line)
{
    if (!line || !*line
    	|| check_oper('|', line, 1)
		|| check_oper('<', line, 2)
		|| check_oper('>', line, 2)
		|| check_chars(line,"\\;&")
		|| check_pipe(line))
	{
		return (0);
	}
    return (1);    
}