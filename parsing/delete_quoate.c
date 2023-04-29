/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quoate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:23 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/29 17:52:52 by oel-houm         ###   ########.fr       */
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

	//after_q = 0;
	end_q = *i + 1;
	while (tok[end_q] != found)
		end_q++;
	//printf("start_quote = %d\n",*i);
	//printf("end_q = %d\n",end_q);
	before_q = ft_substr(tok, 0, *i);
	//printf("before_q = %s\n",before_q);
	inside_q = ft_substr(tok, *i + 1, end_q - *i - 1);
	//printf("inside_q = %s\n",inside_q);
	new = ft_strjoin(before_q, inside_q);
	//printf("new = %s\n",new);
	free(before_q);
	free(inside_q);
	after_q = ft_substr(tok, end_q + 1, 1000);
	//printf("after_q = %s\n",after_q);
	free(tok);
	tok = ft_strjoin(new,after_q);
	free(new);
	free(after_q);
	return (tok);
}

static char *delete_it(char *tok, char found)
{
	int	i;

	i = 0;
	// printf("tok = %s\n",tok);
	while (tok[i])
	{
		if(tok[i] == found)
			tok = remove_quoate(tok,&i,found);
		i++;
	}
	return (tok);
}



void    delete_quoate(char **cmd)
{
	int i;
	char found;
	int j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '"') || ft_strchr(cmd[i], '\''))
		{
            j = 0;
			while(cmd[i][j])
			{
				if(cmd[i][j] == '\'' || cmd[i][j] == '"')
				{
					found = cmd[i][j];
					break;
				}
				j++;
			}
			cmd[i] = delete_it(cmd[i],found);
		}
		// printf("cmd[i] = %s\n",cmd[i]);
		// printf("--------------------\n");
		i++;
	}
	//printf("delete_qouate === %s\n", cmd[1]);
}