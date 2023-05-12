/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-houm <oel-houm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:00:56 by wbouwach          #+#    #+#             */
/*   Updated: 2023/05/12 20:22:41 by oel-houm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_exit;

char    *get_env_value(char *env_var, t_env *env_list)
{
    int env_len;

    if (!env_var)
        return (NULL);
    env_len = ft_strlen(env_var);
    while (env_list->env_name)
    {
        if (ft_strncmp(env_list->env_name, env_var, env_len) == 0)
        {
            return (env_list->env_value);
            break ;
        }
        env_list = env_list->next;
    }
    return (NULL);
}

int find_env(char *env, t_env *env_list)
{
    size_t  i;
    int     len;

    len = ft_strlen(env);
    i = 1;
    while (env_list != NULL)
    {
        if (ft_strncmp(env_list->env_name, env, len) == 0)
        {
            if (ft_strncmp(&env_list->env_name[len + 1], "=", 0) == 0)
                return (i);
            i++;
        }
        else
            i++;
        env_list = env_list->next;
    }
    return (0);
}

// set env_value on the specified env_name
void    set_env(char *env_name, char *env_value, t_env *env_list) // new_env_value 
{
    //size_t  i;
    int     env_len;
    char    *env;
    //char    *tmp;
    //char    *new;
    
    if (!env_name || !env_value)
        return ;
    env_len = ft_strlen(env_name);
    if (find_env(env_name, env_list) > 0) // remove this condition #EXPORT_FIX
    {
        while (env_list->env_name)
        {
            if (ft_strncmp(env_list->env_name, env_name, env_len) == 0)
            {
                free(env_list->env_value);
                env = ft_strdup(env_value); // leaks-fix
                env_list->env_value = env;
                break ;
            }
            env_list = env_list->next;
        }
    }
}

void    parse_cmd(char **cmd, int *tokenised_cmd, t_env *env_list) //,token
{
    if (ft_strncmp(cmd[0], "exit", 4) == 0 && !cmd[0][4])
    {
        (void)env_list;
        exit_cmd(cmd);
        int i = 0;
        while (cmd[i])
        {
            free(cmd[i]);
            i++;
        }
        free(cmd);
    }
    else if (ft_strncmp(cmd[0], "pwd" , 3) == 0 && !cmd[0][3])
    {
        (void)env_list;
        pwd_cmd(cmd);
    }
    else if (ft_strncmp(cmd[0], "echo", 4) == 0 && !cmd[0][4])
    {
        (void)env_list;
        delete_quoate(cmd);
        echo_cmd(cmd, tokenised_cmd);
    }
    else if (ft_strncmp(cmd[0], "env", 3) == 0 && !cmd[0][3])
    {
        env_cmd(cmd, env_list);
    }
    else if (ft_strncmp(cmd[0], "cd", 2) == 0 && !cmd[0][2])
        cd_cmd(cmd, env_list);
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
        export_cmd(cmd, env_list);
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        unset_cmd(cmd, env_list);
    else
        write(1, ":(\n", 3);
}

// char** splitByPipe(char* input, int* tokens, int num_tokens)
// {
//     (void)tokens;
//     char* copy = strdup(input);  // Create a copy of the input string
//     char** result = malloc((num_tokens+1) * sizeof(char*));  // Allocate memory for the result array
//     int start = 0, end = 0, i, j = 0;

//     for (i = 0; i < num_tokens; i++) {
//         // Find the start and end positions of the next token
//         start = end;
//         while (copy[end] != '|' && copy[end] != '\0') {
//             end++;
//         }
//         // Allocate memory for the token and copy it into the result array
//         result[j++] = strndup(copy + start, end - start);
//         // Advance the end position to the next character
//         end++;
//     }
//     // Add a NULL terminator to the end of the result array
//     result[j] = NULL;
//     free(copy);
//     return result;
// }

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
		if (ft_strncmp(cmd[i], "|", ft_strlen(cmd[i]) + 1) != 0 && trigger == 0)
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

char    **cmd_split(char **s, int *tokens)
{
    int     num_of_cmds;
    char    **cmds;
    int     i;
    int     j;

    num_of_cmds = count_cmds(s, '|');
    cmds = malloc(sizeof(char*) * (num_of_cmds + 1));
    i = 0;
    j = 0;
    while (s && s[i] != NULL)
    {
        if (tokens[i] != 6)
        {
            if (cmds[j] == NULL)
            {
                cmds[j] = ft_strdup(s[i]);
                printf("%s\n", cmds[j]);
                printf("%s\n", s[i]);
            }
            else
            {
                //cmds[j] = ft_strjoin(cmds[j], s[i]);
            }
        }
         else if (tokens[i] == 6)
            j++;
        //printf("%d\t%s\n", tokens[i], s[i]);
        i++;
    }
    printf("%s\n", cmds[0]);
    cmds[j] = NULL;
    return (cmds);
}

char** split_cmds(int* tokens, char** cmds)
{
    int num_of_cmds = 0;
    int i, j;
    char** result;

    num_of_cmds = count_cmds(cmds, '|');
    result = (char**)malloc(sizeof(char*) * (num_of_cmds + 1));
    // Split the commands based on tokens
    j = 0;
    result[0] = cmds[0];
    for (i = 1; cmds[i] != NULL; i++) {
        if (tokens[i] == 6) {
            result[j + 1] = cmds[i];
            cmds[i] = NULL;  // Set the original command to NULL
            j++;
        } else {
            result[j] = cmds[i];
        }
    }

    // Set the last element of the result array to NULL
    result[num_of_cmds] = NULL;

    return result;
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
            j++;
        }
        else if (tokens[i] == 6 && flag == 1)
        {
            flag = 0;
            free(cmds[i]);
            cmds[i] = NULL;
            //j++;
        }
        //printf("%d\t%s\n", tokens[i], cmds[i]);
        i++;
    }
    cmd_ptr[j] = NULL;
    return (cmd_ptr);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *cmd;
    t_env *env_list;
    (void)av;
    if (ac > 1)
    {
        printf("Error: too many arguments\n"); // this
        return (127);
    }
    env_list = create_env_list(env);
    //prompt(env_list);
    cmd = readline(BLUE"MINISHELL$ "WHITE);
    global_exit = 0;
    while (1)
    {
        if (*cmd)
            add_history(cmd);
        if (parse(cmd))
        {
            int i = 0;
            //printf("%s\n", parse_operator(cmd));
            //free(cmd);
            cmd = parse_operator(cmd);
            char **s = args_split(cmd);
            //int *t = tokenise_cmd(s);
            // split cmd between pipes
           // while(s && s[i])
            //{
                //parse_cmd -> parse_builtins
                //printf("%s ===== %d\n",s[i],t[i]);
                //int j = 0;
                //while (s[j])
                //{
                 //   printf("%s\n", s[j]);
                  //  j++;
               // }
     cmd = parse_operator(cmd);
     s = args_split(cmd);
     int num_of_cmds = count_cmds(s, '|');
    int *t = tokenise_cmd(s);
    char ***yes = cmd_ptr(s, t);
            //    (void)env_list;
            //    (void)s;
            //    (void)tt;
               int l = 0;
               int d = 0;
               //int num_of_cmds = count_cmds(sz, '|');
               //int num_of_cmds = count_cmds(s, '|');
               //printf("%d", num_of_cmds);
               while (l < num_of_cmds)
               {
                    d = 0;
                    while (yes[l][d])
                    {
                        //printf("%s ", yes[l][d]);
                        // if (yes[l][d + 1] == NULL)
                        //     printf("before:\n%s       after:%s\n", yes[l][d], yes[l][d + 1]);
                        d++;
                    }
                    //printf("\n");
                    l++;
                }
                int pid = fork();
                int status;
                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                if (pid == 0)
                {
                    execvp(yes[0][0], yes[0]);
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    wait(&status);
                    //printf("pid else parent \n");
                    //execvp(yes[0][0], yes[0]);
                }
                //execvp(yes[0][0], yes[0]);
               //expand(s, t, env_list);
               //parse_cmd(s, t, env_list);
               i++;
            //}
        }
       // prompt(env_list);
       // free(cmd);
        cmd = readline(BLUE"MINISHELL$ "WHITE);
    }
    return (global_exit);
}



/*

env -i ./minishell
<Makefile>yy
code sort_env_list func

char* input_string = "echo 'hello_world' >> outfile | ls -l | wc -l >> outfile_2"; =>to=>char**
Echo	            ===	1
'hello wolrd'	    ===	2
>>                  ===	7
outfile             ===	8
|                   ===	6 NULL
ls                  ===	1
-l                  ===	2
|                   ===	6 NULL
wc                  ===	1
-l                  ===	2
>>                  ===	7
outfile_2	        ===	8
NULL                === 0 NULL
char    **split_cmd_by_pipe(char **cmd_split, int *tokens)
{
    // declarations
    int i;

    i = 0;
    //
}


*/

//char **cmd_ptr = malloc x 3;



/*
char **s = {"echo", "'hello_world'", ">>", "outfile", "|", "ls", "-l", "|", "wc", "-l", ">>", "outfile_2"};

char ***cmd_ptr;
char cmd_ptr[0];
char cmd_ptr[1];
char cmd_ptr[2];
...
int *t = 1 2 x x 6 ;



tokinise(cmd_ptr[0]);
*/