/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:21:38 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/10 23:12:27 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


static int	count_strings(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int	ft_strlen_sep(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != c))
		i++;
	return (i);
}

char	*ft_word(char *str, char c)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, c);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (NULL);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**strings;
	int		i;
	int		total_strs;

	i = 0;
	total_strs = count_strings((char *)s, c);
	strings = (char **)malloc(sizeof(char *) * total_strs + 1);
	if (!strings)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			strings[i] = ft_word((char *)s, c);
			i++;
		}
		while (*s && !(*s == c))
			s++;
	}
	strings[i] = 0;
	return (strings);
}

int	count_cmds(char **cmd, char c)
{
	int	i;
	int	trigger;
	int	count;

	(void)c;
	i = 0;
	trigger = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])) != 0 && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])) == 0)
			trigger = 0;
		i++;
	}
	return (count);
}

int	main()
{
	//char *cmd = "echo 'hello_world' >> outfile | ls -l | wc -l >> outfile_2 | ls";
	char *cmd = "echo 'hello_world' >> outfile";
	char **input = ft_split(cmd, ' ');
	printf("total is %d", count_cmds(input, '|'));
	return (0);
}
