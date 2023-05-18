/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:26 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/19 00:20:30 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int check_double_pipe(int *token_arr)
{
	int i;

	i = 0;
	while (token_arr[i])
	{
		if (token_arr[i] == PIPE && token_arr[i + 1] == PIPE)
		{
			write (2,"syntax error two pipe in a row\n",31);
			return (1);
		}
		i++;
	}
	return (0);
}


static int check_next_oper(int *token_arr)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (token_arr[i])
	{
		if(token_arr[i] == HEREDOC_SIG && token_arr[i + 1] != HEREDOC_LIM)
			flag = 1;
		if(token_arr[i] == R_OUT_SIG && token_arr[i + 1] != R_OUT_FILE)
			flag = 1;
		if(token_arr[i] == R_APP_SIG && token_arr[i + 1] != R_APP_FILE)
			flag = 1;
		if(token_arr[i] == R_IN_SIG && token_arr[i + 1] != R_IN_FILE)
			flag = 1;
		i++;
	}
	if (flag)
	{
		ft_putstr_fd("minishell: syntax error: near unexpected token\n",2);
		return (1);
	}
	return (0);
}

static int pipe_in_end(int *token_arr)
{
	int i;

	i = 0;
	while (token_arr[i])
		i++;
	if (token_arr[i - 1] && token_arr[i - 1] == PIPE)
	{
		write(2,"syntax error near `|'\n", 23);
		return (1);
	}
	return (0);
}


// to do 

// adding herdoc delim


int parse_token(int *token_arr)
{
	if (check_double_pipe(token_arr) || check_next_oper(token_arr) || pipe_in_end(token_arr))
	{
		global_exit = 80;
		return (0);
	}
	return (1);
}