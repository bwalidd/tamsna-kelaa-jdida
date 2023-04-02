#include "../minishell.h"

static char	*check_operator_after(char *cmd, int i, int *len)
{
	if ((cmd[i + 1] && cmd[i + 1] != ' ' && !is_redirection(cmd[i + 1])) || *len == 2)
	{
		cmd = add_space_arround(cmd,i,"after");
		*len = 0;
	}
	else
		*len = 0;
	return (cmd);
}


static char	*parse_operator2(char *line)
{
	int		i;
	int		flag;
	char	*cmd;
	int		len;

	len = 0;
	i = 0;
	flag = 0;
	cmd = ft_strdup(line);
	free (line);
	while (cmd[i])
	{
		quoate_flag(&flag, cmd[i]);
		if (flag == 0 && (is_redirection(cmd[i]) || cmd[i] == '|'))
		{
			if (is_redirection(cmd[i]))
				len++;
			// before .. cat makefile |wc -l >>file
			cmd = check_operator_after(cmd, i, &len);
			// after .. cat makefile | wc -l >> file
		}
		i++;
	}
	return (cmd);
}

static char	*add_space_arround(char *str, int i, char *line)
{
	char	*str1;
	char	*str2;
	char	*full_str;

	if (line == "before")
	{
		str1 = ft_substr(str, 0, i);
		str2 = ft_strjoin(str1 , " ");
		free(str1);
		str1 = ft_substr(str,i,1000);
		full_str = ft_strjoin(str2, str1);
	}
	else if (line == "after")
	{
		str1= ft_substr(str,0,i + 1);
		str2= ft_strjoin(str1, " ");
		free(str1);
		str1 = ft_substr(str, i + 1 , 1000);
		full_str(str2, str1);
	}
	free(str1);
	free(str2);
	free(str);
	return (full_str);
}

char    *parse_operator(char *line)
{
	int	i;
	int	flag;
	char	*cmd;

	i = 0;
	flag = 0;
	cmd = ft_strdup(line);
	free (line);
	while (cmd[i])
	{
		quoate_flag(&flag, cmd[i]);
		if (flag == 0 && (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|'))
		{
			if (i > 1 && ft_strlen(cmd) > 1 && cmd[i - 1] != ' ' && !is_redirection(cmd[i - 1]))
			{
				// before ..  cat echo $USER|wc -l>>file
				cmd = add_space_arround(cmd, i, "before");
				// after .. cat echo $USER |wc -l >>file
			}
		}
		i++;
	}
	cmd = parse_operator2(cmd);
	return (cmd);
}
