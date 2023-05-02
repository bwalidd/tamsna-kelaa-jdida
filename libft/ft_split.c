/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:05:16 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/02 13:39:00 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	//int	i;
	int	count;

	//i = 0;
	count = 0;
	while (*s != c && *s)
	{
		count ++;
		s++;
	}
	return (count);
}

static char	*tab_make(char *s, char c)
{
	int		wo_len;
	char	*tab;
	int		i;

	i = 0;
	wo_len = word_len(s, c);
	tab = malloc(sizeof(char) * (wo_len + 1));
	if (!tab)
		return (NULL);
	while (s[i] && i < wo_len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		ins_word;
	char	**result;

	ins_word = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			result[ins_word] = tab_make((char *)s, c);
			ins_word++;
		}
		while (*s && *s != c)
			s++;
	}
	result[ins_word] = 0;
	return (result);
}
