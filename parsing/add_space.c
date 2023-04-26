/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:20 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/26 17:31:38 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_space_arround(char *str, int i, char *line);

static char	*check_operator_after(char *cmd, int i, int *len)
{
	if ((cmd[i + 1] && cmd[i + 1] != ' ' && !is_redirection(cmd[i + 1])) || *len == 2)
	{
		cmd = add_space_arround(cmd,i,"after");
		*len = 0;
	}
	else
		*len = 0;
	return (cmd);
}


static char	*parse_operator2(char *line)
{
	int		i;
	int		flag;
	char	*cmd;
	int		len;

	len = 0;
	i = 0;
	flag = 0;
	cmd = ft_strdup(line);
	free (line);
	while (cmd[i])
	{
		quoate_flag(&flag, cmd[i]);
		if (flag == 0 && (is_redirection(cmd[i]) || cmd[i] == '|'))
		{
			while (is_redirection(cmd[i]))
			{
				len++;
				i++;
			}
			if (is_redirection(cmd[i - 1]))
				i--;
			cmd = check_operator_after(cmd, i, &len);
		}
		i++;
	}
	return (cmd);
}

static char	*add_space_arround(char *str, int i, char *line)
{
	char	*str1;
	char	*str2;
	char	*full_str;

	str1 = NULL;
	str2 = NULL;
	full_str = NULL;
	if (ft_strcmp(line, "before") == 0)
	{
		str1 = ft_substr(str, 0, i);
		str2 = ft_strjoin(str1 , " ");
		free(str1);
		str1 = ft_substr(str,i,1000);
		full_str = ft_strjoin(str2, str1);
	}
	if (ft_strcmp(line, "after") == 0)
	{
		str1= ft_substr(str,0,i + 1);
		str2= ft_strjoin(str1, " ");
		free(str1);
		str1 = ft_substr(str, i + 1 , 1000);
		full_str = ft_strjoin(str2, str1);
	}
	free(str1);
	free(str2);
	free(str);
	return (full_str);
}

char    *parse_operator(char *line)
{
	int	i;
	int	flag;
	char	*cmd;

	i = 0;
	flag = 0;
	cmd = ft_strdup(line);
	while (cmd[i])
	{
		quoate_flag(&flag, cmd[i]);
		if (flag == 0 && (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|'))
		{
			if (i > 1 && ft_strlenn(cmd) > 1 && cmd[i - 1] != ' ' && !is_redirection(cmd[i - 1]))
			{
				// before ..  cat echo $USER|wc -l>>file
				cmd = add_space_arround(cmd, i, "before");
				// after .. cat echo $USER |wc -l >>file
			}
		}
		i++;
	}
	cmd = parse_operator2(cmd);
	return (cmd);
}

// echo ls | wc-l >> file echo "wc -l |"