#include "../includes/minishell.h"



int             builtin_echo(char **args)
{
    // if (!strcmp(args[1],"-n"))
    //     printf("%s",str);
    // else
    //     printf("%s\n",str);
    return (0);
}


int             builtin_cd(char **args)
{
    chdir(args[1]);
    return (1);
}


int             builtin_pwd(void)
{
    char        buf[MAXPATHLEN];

    printf("%s\n",getcwd(buf,MAXPATHLEN));
    return (1);
}


int             builtin_export(char **args)
{
    
}


int             builtin_unset(char **args)
{
    return (0);
}


int             builtin_env(char **envp)
{
    int         i;

    i = 0;
    while (envp[i])
        printf("%s\n",envp[i++]);
    return (1);
}


int             builtin_exit(char **args)
{
    int num = ft_atoi(args[0]);
    exit(num);
}