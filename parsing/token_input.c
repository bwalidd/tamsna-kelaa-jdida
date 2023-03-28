#include "../minishell.h"


static void define_oper(char *cmd, int *cmd_type,int **cmd_in_pipe)
{
    if (cmd[0] == '|')
    {
		*cmd_type = PIPE;
        // to be fixed in below
        **cmd_in_pipe = 0;
    }
	else if (ft_strlen(cmd) > 1 && cmd[0] == '<')
		*cmd_type = HEREDOC_SIG;
	else if (ft_strlen(cmd) > 1 && cmd[0] == '>')
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
    if (!cmp_type)
        return (NULL);
    i = 0;
    cmd_in_pipe = 0;
    while (cmd[i])
    {
        define_token(&cmd_type,i,cmd,&cmd_in_pipe);
        i++;
    }
    // to do check_tokens
}