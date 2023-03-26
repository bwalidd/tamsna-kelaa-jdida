#include "../../minishell.h"

int check_chars(char *line, char *str)
{
    int i;
    int flag;
    int j;

    i = 0;
    flag = 0;
    while (line[i])
    {
        j = 0;
        quoate_flag(&flag, line[i]);
        while (flag == 0 && str[j])
        {
            if(line[i] == str[j])
            {
                write(2,"syntax error\n",13);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}