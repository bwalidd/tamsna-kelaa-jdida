#include "../../minishell.h"

int check_unsupport(char *line)
{
    int i;
    int flag;

    i = 0;
    flag = 0
    while (line[i])
    {
        quoate_flag(&flag,line[i]);
        if((line[i] == '>' && state == 0) || (state == 0 && line[i] == '<'))
        {
            if ((line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '<' && line[i + 1] == '>'))
			{
                write(2,"syntax error\n",13);
                return (1);
            }
        }
        i++;
    }
    return (0);
}