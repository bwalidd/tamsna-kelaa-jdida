/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:52:38 by oel-houm          #+#    #+#             */
/*   Updated: 2023/04/27 03:42:05 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "../minishell.h"



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


/*
static void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], fd);
		i++;
	}
}
*/


/*
 * 
 * static void	free_exit(char **cmd)
 *
 *
 * */



static int	number_of_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
	{
		//printf("args[%d]: %s\n", count, args[count]);
		count++;
	}
	//printf("count:%d\n", count);
	return (--count);
}

static int	ft_isnum(char *str) // ft_isnum ft_isdigit
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void		exit_cmd(char **cmd) // exit_cmd takes 2 params: cmd + copy_of_env
{
	//
	//
	if (number_of_args(cmd) > 1)
	{
		//1-freeing all args from memory before printing error
		//2-print exit
		//3-print minishell: exit: too many arguments
		//4-set exit status to 1
		if (cmd[1] && ft_isnum(cmd[1]) != 1)
		{
			//ft_putstr_fd("exit\n", 2);
			//ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			printf("exit\nminishell: exit: $(args): numeric argument required\n");
		}
		else if (cmd && ft_isnum(cmd[1]) == 1)
		{
			printf("exit\nminishell: exit: too many arguments\n");
		}
		int i = 0;
		while (cmd[i] != NULL)
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
	else if (number_of_args(cmd) == 1)
	{
		if (!(ft_isnum(cmd[1])))
		{
			//
			printf("exit\nminishell: exit: $(args): numeric argument required\n");
		}
		int exit_value = atoi(cmd[1]); //fix ft_atoi.c + change the value of $? in ENV
		int i =0;
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		printf("exit\n");
		exit(exit_value);// check if cmd[1] is num then convert from char to int...
		//execvp(cmd[0], cmd);
	}
	else if (number_of_args(cmd) == 0)
	{
		int		i;

		i = 0;
		// freeing the cmd before exiting
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		//ft_putstr_fd("exit\n", 1)
		printf("exit\n");
		exit(0);
	}
}

int	main()
{
	//char *str[] = {"exit", "42", NULL};
	//char *str[] = {"exit", "42", "9", NULL};
	//char *str[] = {"exit", NULL};
	char **str = ft_split("exit 13 54", ' ');
	exit_cmd(str);
	return (0);
}
