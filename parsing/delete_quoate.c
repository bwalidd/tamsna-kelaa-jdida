/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quoate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:23 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/12 21:23:48 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *remove_quoate(char *tok, int *i)
{
	char	*before_q;
	char	*inside_q;
	char	*new;
	int		end_q;

	end_q = *i + 1;
	while (tok[end_q] != '\'' && tok[end_q] != '"')
		end_q++;
	before_q = ft_substr(tok, 0, *i);
	inside_q = ft_substr(tok, *i + 1, end_q - *i - 1);
	new = ft_strjoin(before_q, inside_q);
	free(before_q);
	free(inside_q);
	*i = end_q - 2;
	before_q = ft_strjoin(new, tok + end_q + 1);
	free(tok);
	free(new);
	tok = ft_strdup(before_q);
	free(before_q);
	return (tok);
}


static char *delete_it(char *tok)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if(tok[i] == '\'' || tok[i] == '"')
			tok = remove_quoate(tok,&i);
		i++;
	}
	return (tok);
}

void    delete_quoate(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] && (ft_strchr(cmd[i], '"') || ft_strchr(cmd[i], '\'')))
				cmd[i] = delete_it(cmd[i]);
		i++;
	}
}