#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define STDIN	0
#define STDOUT	1
#define STDERR	2

void	piping(char **cmd, int infile, int outfile)
{
	int fd[2];
	int	pid;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], outfile); //stdfileno//outfile
		close(fd[0]);
		close(fd[1]);
		execvp(cmd[0], cmd);
	}
	dup2(fd[0], infile);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}

int	main(void)
{
	char	*cmd[][4] =
	{
		{"ls", "-l", NULL},
		{"pwd", NULL},
		{"cat", "infile", NULL, "outfile", NULL},
		{"ls", "-la", NULL},
		{"cat", NULL},
		{"cat", NULL},
		//{"pwd", NULL}, // redirect to out.txt
		//{"cat", NULL},
		//{"man", "cat", NULL},
		{"tail", NULL}, // redirect to STDOUT
		//{"echo", "4242424242", NULL},
	};
	int	int_fd;
	int	num_of_cmds = 6;
	int	stdin_copy = dup(STDIN);
	int	stdout_copy = dup(STDOUT);
	int i = 0;
	int out_fd = STDOUT;
	//int out_fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
	while (i < num_of_cmds - 1)
	{
		if (i == 1)
		{
			out_fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(out_fd, STDOUT);
		}
		else
		{
			out_fd = STDOUT;
			//dup2(stdout_copy, out_fd);
		}
		piping(cmd[i], STDIN, out_fd);
		if (i == 1)
		{
			//close(out_fd);
			out_fd = STDOUT;
			//dup2(stdout_copy, out_fd);
		}
		i++;
	}
	// ila bghit nredirecti flakher lchi outfile dup2(open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644), STDOUT);
	dup2(stdout_copy, STDOUT);
	//dup2(, STDOUT);
	execvp(cmd[i][0], cmd[i]);
	return (0);
}

