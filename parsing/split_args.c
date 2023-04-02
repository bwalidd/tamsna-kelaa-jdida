#include "../minishell.h"





static int arg_len_counter(char *cmd)
{
    int i;
    int flag;

    flag = 0;
    i = 0;
    while (cmd && cmd[i])
    {
        if (cmd[i] == '\'' || cmd[i] == '"')
            quoate_flag(&flag,cmd[i]);
        i++;
        if (is_space(cmd[i]) && flag == 0)
            break;
    }
    return (i);
}

/*
 cat
makefile
 |
 wc 
 -l 
 >> 
 file 
 */
static int count_args(char *cmd)
{
    int i;
    int count;
    int flag;

    flag = 0;
    count = 0;
    i = 0;
    while (cmd && cmd[i])
    {
        if (cmd[i] == '\'' || cmd[i] == '\"')
            quoate_flag(&flag,cmd[i]);
        i++;
        if (is_space(cmd[i]) && flag == 0)
        {
            while (cmd[i] && is_space(cmd[i]))
                i++;
            if (cmd[i])
                count++;
        }
    }
    return (count + (flag == 0));
}

char    **args_split(char *cmd)
{
    char    **split;
    int     nb_args;
    int     arg_len;
    int     i;
    int     check;

    while (cmd && *cmd && is_space(*cmd))
        cmd++
    nb_args = count_args(cmd);
    split = malloc((nb_args + 1) * sizeof(char *));
    split[nb_args] = NULL;
    i = 0;
    while (i < nb_args)
    {
        check = 0;
       arg_len = arg_len_counter(cmd);
       split[i] = ft_substr(cmd,0,arg_len);
       if (cmd[arg_len] != '\0')
            check = 1;
       cmd = cmd + arg_len + check;
       while (*cmd && is_space(*cmd))
            cmd++;
        i++;
    }
    return (split);
}