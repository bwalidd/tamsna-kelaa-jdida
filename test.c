#include <stdio.h>



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


int is_unclosed_quotes(char *line)
{
    int i;
    char quotes;

    i = 0;
    
    if (!ft_strchr(line, '\'') && !ft_strchr(line, '\"'))
        return (0);
    while (line[i])
    {
        quotes = '1';
        if (line[i] == '\'' || line[i] == '\"')
        {
            quotes = line[i];
            if(line[i + 1] == quotes)
            {
                i++;
                continue;
            }   
            i++;
            while (line[i] && line[i] != quotes)
            {
                i++;
                if (line[i] == quotes)
                {
                    quotes = '0';
                    break;
                }
                
            }
        }
        i++;
    }
    if (quotes != '1')
    {
        return (printf("minishell: unclosed quotes\n"), 1);;
        
    }
    return (0);
}

int main() {
  char *s = "echo ls cat";
  if (is_unclosed_quotes(s))
  {
    printf("lbdr zaml");
  }
  else
  {
  
    printf("bxm mqwd");
    }
  return 0;
}