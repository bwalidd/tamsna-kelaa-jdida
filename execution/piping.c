/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:19:50 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/21 17:27:36 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    piping(char **cmd, int infile, int outfile, char **env, t_env *env_list, int *token) // t_env env_list
{
    int fd[2];
    int pid;
    int status;
    (void)env;

    (void)token;
    (void)env_list;

    pipe(fd);
    pid = fork(); // handle fork perror 
    if (pid == 0)
    {
        dup2(fd[1], outfile);
        close(fd[0]);
        close(fd[1]);
        if (is_builtins(cmd[0]) == 1)
        {
            //exit(1);
            exec_builtins(cmd, token, env_list); //// handle exit here 
            exit(0);
        }
        else
            exec_cmd(cmd, env);
    }
    dup2(fd[0], infile);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        global_exit = WEXITSTATUS(status);
        //printf("Child process exited with status: %d\n", global_exit);
        // Handle exit status as needed
    }
    else
    {
        //printf("Child process terminated abnormally\n");
        // Handle abnormal termination as needed
    }
}
