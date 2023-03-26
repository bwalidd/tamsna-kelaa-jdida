#include "../../minishell.h"

int check_pipe(char *line)
{
    if (*line == '|')
    {
        write(2,"syntax error\n",13);
        return (1);
    }
    return (0);
}