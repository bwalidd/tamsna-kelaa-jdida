#include "minishell.h"

/*
 # find_env_value		#
 # get_env_value		#
 # find_env				#
 # set_env				#
*/

typedef struct s_env
{
	char    *env_name;
	char    *env_value;
	struct s_env *next;
	struct s_env *prev;
}               t_env;


int find_env(char **env, t_env *env_list)
{
    size_t  i;
    int     len;

    len = ft_strlen(env);
    i = 0;
    while (env_list != NULL)
    {
        if (ft_strncmp(env_list->env_name, env, len) == 0)
        {
            if (ft_strncmp(env_list->env_name[len + 1], "=", 0) == 0)
                return (i);
            i++;
        }
        else
            i++;
        env_list = env_list->next;
    }
    return (0);
}

void    set_env(char *env, char *new_env, t_env *env_list) // set_env("PWD", pwd)
{
    size_t  i;
    int     len;
    char    *tmp;
    char    *new;

    if (!env || !new_env)
        return;
    len = ft_strlen(env);
    i = find_env(env, env_list);
    if (i != 0)
    {
        tmp = ft_substr(env_list);
    }
}
