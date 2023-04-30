/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quoate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:23 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/30 15:14:21 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*apply_delete(char *tok, int *i)
{
	char	*tmp[2];
	char	*new_tok;
	char	quote;
	int		j;

	quote = tok[*i];
	j = *i + 1;
	while (tok[j] != quote)
		j++;
	tmp[0] = ft_substr(tok, 0, *i);
	tmp[1] = ft_substr(tok, *i + 1, j - *i - 1);
	new_tok = ft_strjoin(tmp[0], tmp[1]);
	free (tmp[0]);
	free (tmp[1]);
	*i = j - 2;
	tmp[0] = ft_strjoin(new_tok, tok + j + 1);
	free (tok);
	free (new_tok);
	tok = ft_strdup(tmp[0]);
	free (tmp[0]);
	return (tok);
}
/*
echo

-n"haahah hhaaha hajaoai"

*/
static char	*delete_quoate_tok(char *tok)
{
	int		i;

	i = 0;
	while (tok[i])
	{
		if (tok[i] == '\'' || tok[i] == '"')
			tok = apply_delete(tok, &i);
		i++;
	}
	return (tok);
}

void	delete_quoate(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] && ft_strchr(cmd[i], '\'')) || (cmd[i] && ft_strchr(cmd[i], '"')))
			cmd[i] = delete_quoate_tok(cmd[i]);
		i++;
	}
}