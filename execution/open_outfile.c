/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:47:13 by oel-houm          #+#    #+#             */
/*   Updated: 2023/05/25 02:42:27 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	set_output_redirect_to_null(char **cmd, int *cmd_tokens)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd_tokens[i] == 4 || cmd_tokens[i] == 7) // || cmd_tokens[i] == 0 || cmd_tokens[i] == 0
			cmd[i] = NULL;
		i++;
	}
}

int		get_output_redirection_index(int *cmd_tokens, t_redirection *redirection)
{
	int	i;

	i = 0;
	while (cmd_tokens[i])
    {
        if (cmd_tokens[i] == 4 || cmd_tokens[i] == 7)
        {
            redirection->out_redirection_token = cmd_tokens[i];
			return (i);
        }
        i++;
    }
	return (0); // return ;
}

int		get_outfile_index(int *cmd_tokens, int index)
{
	while (cmd_tokens[index])
	{
		if (cmd_tokens[index] == 5 || cmd_tokens[index] == 8)  //// !!! may be
        {
            return (index);
        }
		index++;
	}
	return (0); // return ;
}

void	establish_output_stream(char **cmd, int *cmd_tokens, t_redirection *redirection)
{
	redirection->out_redirection_token = 0;
	redirection->out_redirection_index = 0;
	redirection->outfile_index = 0;
	redirection->outfile = NULL;
	redirection->out_fd = STDOUT;
	
	redirection->stdin_copy = STDIN;
	redirection->stdout_copy = STDOUT;

	redirection->out_redirection_index = get_output_redirection_index(cmd_tokens, redirection);
	redirection->outfile_index = get_outfile_index(cmd_tokens, redirection->out_redirection_index);
	redirection->outfile = cmd[redirection->outfile_index];
	if (redirection->out_redirection_index != 0 && redirection->outfile_index != 0)
	{
		if (redirection->out_redirection_token == 4)
			redirection->out_fd = open(redirection->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		else if (redirection->out_redirection_token == 7)
			redirection->out_fd = open(redirection->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (redirection->out_fd == -1)
    	{
        	ft_putstr_fd("minishell: ", 2);
            perror(redirection->infile); // no such file or dir ????????
            exit(1);
    	}
	}
	set_output_redirect_to_null(cmd, cmd_tokens); // set output token to null
}




void    set_input_redirect_to_null(char **cmd, int *cmd_tokens)
{
        int i;

        i = 0;
        while (cmd[i])
        {
                if (cmd_tokens[i] == 3) // yes
                        cmd[i] = NULL;
                i++;
        }
}

int             get_input_redirection_index(int *cmd_tokens, t_redirection *redirection)
{
        int     i;

        i = 0;
        while (cmd_tokens[i])
        {
                if (cmd_tokens[i] == 3) //yes
                {
                        redirection->in_redirection_token = cmd_tokens[i];
                        return (i);
                }
                i++;
        }
        return (0); // return ;
}

int             get_infile_index(int *cmd_tokens, int index)
{
        while (cmd_tokens[index])
        {
                if (cmd_tokens[index] == 5 || cmd_tokens[index] == 8)  //// !!! may be //yes
                {
                        return (index);
                }
                index++;
        }
        return (0); // return ;
}

void    establish_input_stream(char **cmd, int *cmd_tokens, t_redirection *redirection)
{
        redirection->in_redirection_token = 0;
        redirection->in_redirection_index = -2;
        redirection->infile_index = -2;
        redirection->infile = NULL;
        redirection->in_fd = STDIN;

        redirection->stdin_copy = STDIN;
	redirection->stdout_copy = STDOUT;

        redirection->in_redirection_index = get_input_redirection_index(cmd_tokens, redirection);
        //redirection->infile_index = get_infile_index(cmd_tokens, redirection->in_redirection_index);
                redirection->infile_index = redirection->in_redirection_index + 1;
                redirection->infile = cmd[redirection->infile_index];
        if (redirection->in_redirection_index != -2 && redirection->infile_index != -2)   ///// -2 !
        {
                // ndkhel lines .. ldakhl
                if (redirection->in_redirection_token == 3)
                {
                        redirection->in_fd = open(redirection->infile, O_RDONLY);
                }
                if (redirection->in_fd == -1)
                {
                        ft_putstr_fd("minishell: ", 2);
                        perror(redirection->infile); // no such file or dir ????????
                        exit(1);
                }
       }
        set_input_redirect_to_null(cmd, cmd_tokens);
       if (redirection->infile != NULL && redirection->in_redirection_token == 3)
       { cmd[0] = NULL;
        cmd[1] = NULL; 
        cmd[0] = cmd[2];
        }
}

// pwd | < minishell.c cat | wc

// if the cmd[0] == <  then do establish_input_stream() and open file then set cmd[0] = the cmd[2]
// < minishell.c cat dsfdsf | head
// if < kanakhod argg li morah as infile
// manakhod arg li mora infile as cmd o mandir liha ckeck if the cmd ixist or not ila la kandir perror and exit
// ila kan chi arg mora cmd kanmchi nchof wach howa file and wach it exist ila ah kanrj3o howa li infile

// < file1 cat file2 file1

// if infile and i == 0

// pwd | < makefile catdf | head
// 
