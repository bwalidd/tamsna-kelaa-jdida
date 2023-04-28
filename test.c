#include <stdio.h>
#include <stdlib.h>
int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*p;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s && i < len && start < ft_strlen(s))
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}


int is_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

void    quoate_flag(int *flag, int c)
{
    if (c == '\'')
    {
        if (*flag == 1)
            *flag = 0;
        else if (*flag == 0)
            *flag = 1;
    }
    if (c == '"')
    {
        if (*flag == 2)
            *flag = 0;
        else if (*flag == 0)
            *flag = 2;
    }
}
 

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
    //echo "'hello' there" == 2
    //echo 'hello' there == 3
}

char    **args_split(char *cmd)
{
    char    **split;
    int     nb_args;
    int     arg_len;
    int     i;

    while (cmd && *cmd && is_space(*cmd))
        cmd++;
    nb_args = count_args(cmd);
    split = malloc((nb_args + 1) * sizeof(char *));
    split[nb_args] = NULL;
    i = 0;
    while (i < nb_args)
    {
       arg_len = arg_len_counter(cmd);
       split[i] = ft_substr(cmd, 0, arg_len); 
       cmd += arg_len;
       while (*cmd && is_space(*cmd))
            cmd++;
        i++;
    }
    return (split);
}


int main() {
  char *cmd = "cat | ls >> file echo                'fvniubeiru'bie vuyyvuy";
    char **s = args_split(cmd);
    int i = 0;
    while(s && s[i]){
      printf("%s\n",s[i]);
      i++;
      }
  return 0;
}