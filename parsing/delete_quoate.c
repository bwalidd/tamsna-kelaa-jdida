#include "../minishell.h"

static char *remove_quoate(char *tok, int *i)
{
	char	*before_q;
	char	*inside_q;
	char	*new;
	int		end_q;

	end_q = *i + 1;
	while (tok[end_q] != '\'' && tok[end_q] != '"')
		end_q++;
	before_q = ft_substr(tok, 0, *i);
	inside_q = ft_substr(tok, *i+1, end_q - *i - 1);
	new = ft_strjoin(before_q, inside_q);
	free(before_q);
	free(inside_q);
	*i = j - 2;
	before_q = ft_strjoin(new, tok + j + 1);
	free(tok);
	free(new);
	tok = ft_strdup(before_q);
	free(before_q);
	return (tok);
}


static char *delete_it(char *tok)
{
	int	i;
	while (tok[i])
	{
		if(tok[i] == '\'' || tok[i] == '"')
			tok = remove_quoate(tok,&i);
		i++;
	}
}

void    delete_quoate(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] && ft_strchr(cmd[i], '"')) || (cmd[i] && ft_strchr('\'')))
				cmd[i] = delete_it(cmd[i]);
		i++;
	}
}