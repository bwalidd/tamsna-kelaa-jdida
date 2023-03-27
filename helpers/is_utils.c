#include "../minishell.h"

int is_redirection(char c)
{
    if (c == '<' || c == '>')
        return (1);
    return (0);
}