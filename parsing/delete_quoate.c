/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quoate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:23 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/14 18:17:36 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *remove_quoate(char *tok, int *i,char found)
{
	char	*before_q;
	char	*inside_q;
	char	*new;
	int		end_q;
	char	*after_q;


	after_q = 0;
	end_q = *i + 1;
	while (tok[end_q] != found)
		end_q++;
	before_q = ft_substr(tok, 0, *i);
	inside_q = ft_substr(tok, *i + 1, end_q - *i - 1);
	new = ft_strjoin(before_q, inside_q);
	free(before_q);
	free(inside_q);
	*i = end_q - 2;
	after_q = ft_substr(tok, end_q, 1000);
	inside_q = ft_strjoin(new,after_q);
	free(tok);
	free(new);
	free(after_q);
	tok = ft_strdup(inside_q);
	free(inside_q);
	return (tok);
}
/*
 echo
 gooo"here is my name '$HOME'"wbouwach
 before_q = gooo
 inside_q = here is my name '$HOME'
 new = gooohere is my name '$HOME'
 before_q = 
*/
static char *delete_it(char *tok, char found)
{
	int	i;

	i = 0;
	while (tok[i])
	{
		if(tok[i] == found)
			tok = remove_quoate(tok,&i,found);
		i++;
	}
	return (tok);
}


void    delete_quoate(char **cmd, t_env *env)
{
	int i;
	char found;

	i = 0;
	while (cmd[i])
	{
		found = '0';
		if (cmd[i] && (ft_strchr(cmd[i], '"') || ft_strchr(cmd[i], '\'')))
		{
			found = cmd[i];
			cmd[i] = delete_it(cmd[i],found);	
			//cmd[i] = apply_expander(cmd[i], env);
		}
		i++;
	}
}