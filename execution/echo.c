/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:40:53 by oel-houm          #+#    #+#             */
/*   Updated: 2023/04/28 15:52:44 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// check cmd_args[0] if is it === "echo"
// start printing what are front of echo cmd

void	echo_cmd(char **line) // echo "salam w3alikom"
{
	// if "echo '" then i = 6;
	int	i;
	char *s;

	i = 6;
	s = *line;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int		main()
{
	char *line[] = {"echo", "'omarr"};
	echo_cmd(line);
	return (0);
}
