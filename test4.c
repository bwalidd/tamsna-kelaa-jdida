#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	while ((s1[a] || s2[a]) && a < n)
	{
		if (s1[a] == s2[a])
			a++;
		else
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
	}
	return (0);
}

int	count_cmds(char **cmd, char c)
{
	int	i;
	int	trigger;
	int	count;

	(void)c;
	i = 0;
	trigger = 0;
	count = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])) != 0 && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])) == 0)
			trigger = 0;
		i++;
	}
	return (count);
}

char ***cmd_ptr(char **cmds, int *tokens)
{
    int num_of_cmds = 0;
    int i;
    int j;
    int flag;
    char ***cmd_ptr;
    //char** current_cmd = cmds;

    num_of_cmds = count_cmds(cmds, '|');
    cmd_ptr = malloc(sizeof(char **) * (num_of_cmds + 1));
    //cmd_ptr[num_of_cmds] = NULL;
    //(void)cmd_ptr;
    i = 0;
    flag = 0;
    j = 0;
    while (cmds && cmds[i] != NULL)
    {
        if (tokens[i] != 6 && flag == 0)
        {
            cmd_ptr[j] = &cmds[i];
            flag = 1;
            //j++;
        }
        else if (tokens[i] == 6 && flag == 1)
        {
            flag = 0;
            //free(cmds[i]);
            cmds[i] = NULL;
            j++;
        }
        //printf("%d\t%s\n", tokens[i], cmds[i]);
        i++;
    }
    cmd_ptr[j] = NULL;
    return (cmd_ptr);
}

int main(void)
{
    char *s[] = {"echo", "'hello_world'", ">>", "outfile", "|", "ls", "-l", "|", "wc", "-l", ">>", "outfile_2"};
	printf("n=%d\n", count_cmds(s, '|'));
	/*
    char *s[] = {"echo", "'hello_world'", ">>", "outfile", "|", "ls", "-l", "|", "wc", "-l", ">>", "outfile_2"};
    int t[] = {1, 2, 7, 8, 6, 1, 2, 6, 1, 2, 7, 8};
    char ***yes = cmd_ptr(s, t);
    int l = 0;
    int d = 0;
    //while (ft_strncmp(yes[l][0], 0, ft_strlen(yes[l][0])) != 0 && yes[l] != NULL)
    while (l <= 15)
    {
        while (yes[l][d])
        {
            printf("%s ", yes[l][d]);
            d++;
        }
        printf("\n");
        l++;
    }*/
    return (0);
}
