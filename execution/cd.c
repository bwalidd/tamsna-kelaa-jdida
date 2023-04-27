/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:23:19 by oel-houm          #+#    #+#             */
/*   Updated: 2023/04/27 05:07:58 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static int	number_of_args(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
	{
		count++;
	}
	return (--count);
}

void		cd_cmd(char **cmd)// cmd(t_token, *env_list[])
{
	char	*path;
	int		err;

	// cd a1 a2 a3 a4    if a1 exist in the pwd, change dir into it and ignore all following args a2,a3,a4
	// free a1,a2,a3,a4
	err = 0;
	if (number_of_args(cmd) > 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		// return value should be returned to minishell as 1
		exit(1);
	}
	else if (number_of_args(cmd) == 1)
	{
		write(1, "=1\n", 3);
		path = cmd[1];
		err = chdir(path);
		// handle PWD and OLDPWD in ENV
		if (err) // handle cd /root : permission denied
		{
			printf("err=%d", err);
		}
	}
	else if (number_of_args(cmd) == 0)
	{
		write(1, "=0\n", 3);
	}
}

int	main()
{
	char *args[] = {"pwd", NULL};
	char **cmd = ft_split("cd /root", ' ');
	cd_cmd(cmd);
	//execvp(args[0], args);
}
