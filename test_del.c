#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	if (dst == src || !n)
		return (dst);
	index = 0;
	while (index < n)
	{
		*((char *) dst + index) = *((char *)src + index);
		index++;
	}
	return (dst);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s1) + 1;
	p = (char *)malloc(len);
	if (!p || !s1)
		return (NULL);
	ft_memcpy(p, s1, len);
	return (p);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*p;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || ft_strlen(s) == 0)
		return (ft_strdup(""));
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

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}



static char *remove_quoate(char *tok, int *i,char found)
{
	char	*before_q;
	char	*inside_q;
	char	*new;
	int		end_q;
	char	*after_q;

	//after_q = 0;
	end_q = *i + 1;
	while (tok[end_q] != found)
		end_q++;
	//printf("start_quote = %d\n",*i);
	//printf("end_q = %d\n",end_q);
	before_q = ft_substr(tok, 0, *i);
	//printf("before_q = %s\n",before_q);
	inside_q = ft_substr(tok, *i + 1, end_q - *i - 1);
	//printf("inside_q = %s\n",inside_q);
	new = ft_strjoin(before_q, inside_q);
	//printf("new = %s\n",new);
	free(before_q);
	free(inside_q);
	after_q = ft_substr(tok, end_q + 1, 1000);
	//printf("after_q = %s\n",after_q);
	free(tok);
	tok = ft_strjoin(new,after_q);
	free(new);
	free(after_q);
	return (tok);
}

static char *delete_it(char *tok, char found)
{
	int	i;

	i = 0;
	printf("tok = %s\n",tok);
	while (tok[i])
	{
		if(tok[i] == found)
			tok = remove_quoate(tok,&i,found);
		i++;
	}
	return (tok);
}



void    delete_quoate(char **cmd)
{
	int i;
	char found;
	int j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '"') || ft_strchr(cmd[i], '\''))
		{
            j = 0;
			while(cmd[i][j])
			{
				if(cmd[i][j] == '\'' || cmd[i][j] == '"')
				{
					found = cmd[i][j];
					break;
				}
				j++;
			}
			cmd[i] = delete_it(cmd[i],found);
		}
		printf("cmd[i] = %s\n",cmd[i]);
		printf("--------------------\n");
		i++;
	}
}

int main(){
char *s = "echo  \"'\"\"'\"hello\"'\"\"'\" hhhhhhh";
char **cmd = ft_split(s, ' ');
   delete_quoate(cmd);
    //int i = 0;
    // while (cmd[i])
    // {
    //     printf("cmd[i] = %s\n",cmd[i]);
    //     i++;
    // }
   
}
