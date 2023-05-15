/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:17:31 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/15 21:33:59 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void	piping(char **cmd, int infile, int outfile)
// ghn7et outfile f 1 as default mn be3d if thereis a file of type outfile dik sa3a nrj3 outfile = openfile(outfile);
{
	int fd[2];
	int ps;
	pipe(fd);
	ps = fork();
	if (ps == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[0]);
		close(fd[1]);
		execvp(cmd[0], cmd);
	}
	//dup2(fd[0], outfile); //stdin
	dup2(fd[0], STDIN);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, WNOHANG);
}

int		main(void)
{
	char *cmd[3][3] =
	{
		{"ls", "-l", NULL},
		{"man", "rm", NULL},
		{"wc", NULL}
	};
	int	num_of_cmds = 3;
	int	i = 0;
    int outfile = open("output.txt", O_WRONLY | O_CREAT, 0644);
    int stdout_copy = dup(STDOUT); // Save a copy of the original stdout file descriptor
    dup2(outfile, STDOUT); // Redirect stdout to the output file
	while (i < num_of_cmds - 1)
	{
		piping(cmd[i], 1, outfile);
		i++;
	}
	execvp(cmd[i][0], cmd[i]);
	dup2(stdout_copy, STDOUT);
    close(outfile);
	return (0);
}
