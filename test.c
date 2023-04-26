#include <stdio.h>



// char    *ft_strchr(const char *s, int c)
// {
//     while (*s)
//     {
//         if (*s == (char)c)
//             return ((char *)s);
//         s++;
//     }
//     if ((char)c == '\0')
//     {
//         return ((char *)s);
//     }
//     return (NULL);
// }


// int is_unclosed_quotes(char *line)
// {
//     int i;
//     char quotes;

//     i = 0;
    
//     if (!ft_strchr(line, '\'') && !ft_strchr(line, '\"'))
//         return (0);
//     while (line[i])
//     {
//         quotes = '1';
//         if (line[i] == '\'' || line[i] == '\"')
//         {
//             quotes = line[i];
//             while (line[i])
//             {
//                 if (line[i + 1] == quotes)
//                 {
//                     quotes = '0';
//                     break;
//                 }
//                 i++;
//                 while(line[i])
//                 {
//                     if (quotes == line[i])
//                     {
//                         quotes = '0';
//                         break;
//                     }
//                     i++;
//                 }
                
//             }
//         }
//         i++;
//     }
//     if (quotes != '1')
//     {
//         printf("minishell: unclosed quotes\n");
//         return (1);
        
//     }
//     return (0);
// }


int check_outside(int nbr)
{
   if(nbr % 2 == 0)
        return (0);
    return (1);
}

int is_unclosed_quoate(char *line)
{
    int double_count;
    int single_count;
    int i;

    double_count = 0;
    single_count = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == '\"')
                if (check_outside(single_count) == 0)
                    double_count++;
        if (line[i] == '\'')
            if (check_outside(double_count) == 0)
                    single_count++;
        i++;
    }
    if (double_count % 2 != 0 || single_count % 2 != 0)
        return (1);
    return (0);
}

int main() {
  char *s = "echo \"ni'uibue'wi\"    hht 'rniunie\"ubsiub'rnuudhius";
  if (is_unclosed_quoate(s))
    printf("unclosed quotes\n");
  else
    printf("closed quotes\n");
  return 0;
}