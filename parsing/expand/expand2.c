#include "../../minishell.h"


char *replace_wrong_name(char *cmd, int *i)
{
    char    *str;
    char    *str2;

    str = ft_strdup(cmd);
    str[*i] = '\0';
    str2 = ft_substr(cmd, (*i) + 2, ft_strlen(str));
    free(cmd);
    cmd = ft_strjoin(str1, str2);
    *i = ft_strlen(str);
    free(str);
    free(str2);
    return (cmd);
}

char    *replacing(char *cmd, int *i)
{
    char    *exit;
    char    *str;
    char    *str2;

    exit = ft_itoa(global_exit);
    str = ft_substr(cmd,0,*i);
    str2 = ft_strjoin(str,exit);
    free(exit);
    free(str);
    str = ft_substr(cmd, (*i) + 2, ft_strlen(cmd));
    free(cmd);
    cmd = ft_strjoin(str2, str);
    *i = ft_strlen(str2);
    free(str1);
    free(str2);
    return (cmd);
}