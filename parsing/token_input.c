/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbouwach <wbouwach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:53:39 by wbouwach          #+#    #+#             */
/*   Updated: 2023/04/25 21:59:18 by wbouwach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void define_oper(char *cmd, int *cmd_type,int **cmd_in_pipe)
{
    if (cmd[0] == '|')
    {
		  *cmd_type = PIPE;
        // to be fixed in below -- true to be tested
        **cmd_in_pipe = 0;
        // note is any thing after | is a CMDNAME
    }
	else if (ft_strlenn(cmd) > 1 && cmd[0] == '<')
		*cmd_type = HEREDOC_SIG;
	else if (ft_strlenn(cmd) > 1 && cmd[0] == '>')
		*cmd_type = R_APP_SIG;
	else if (cmd[0] == '<')
		*cmd_type = R_IN_SIG;
	else if (cmd[0] == '>')
		*cmd_type = R_OUT_SIG;
}

static void define_token(int **cmd_type, int i, char **cmd, int *cmd_in_pipe)
{
    if (*cmd[i] == '<' || *cmd[i] == '>' || *cmd[i] == '|')
        define_oper(cmd[i] , &(*cmd_type)[i] , &cmd_in_pipe);
    else if (i > 0 && (*cmd_type)[i - 1] == R_APP_SIG)
		(*cmd_type)[i] = R_APP_FILE;
    else if (i > 0 && (*cmd_type)[i - 1] == HEREDOC_SIG)
		(*cmd_type)[i] = HEREDOC_LIM;
    else if (i > 0 && (*cmd_type)[i - 1] == R_OUT_SIG)
		(*cmd_type)[i] = R_OUT_FILE;
    else if (i > 0 && (*cmd_type)[i - 1] == R_IN_SIG)
		(*cmd_type)[i] = R_IN_FILE;
    else if ((i > 0 && (*cmd_type)[i - 1] == CMD_NAME)
			|| (i > 0 && (*cmd_type)[i - 1] == CMD_ARG) || *cmd_in_pipe == 1)
		(*cmd_type)[i] = CMD_ARG;
	else
	{
		(*cmd_type)[i] = CMD_NAME;
		*cmd_in_pipe = 1;
	}
}


int *tokenise_cmd(char **cmd)
{
    int cmd_in_pipe;
    int *cmd_type;
    int i;

    cmd_type = ft_calloc(ft_array_size(cmd) + 1 ,sizeof(int));
    if (!cmd_type)
        return (NULL);
    i = 0;
    cmd_in_pipe = 0;
    while (cmd[i])
    {
        define_token(&cmd_type,i,cmd,&cmd_in_pipe);
        i++;
    }
    if(parse_token(cmd_type))
      return (cmd_type); // to do under in exit status
    global_exit = 2;
    free(cmd_type);
    return (0);
}