#include "../includes/minishell.h"












int             sh_launch(char **args, char **envp)
{
  pid_t         pid;
  pid_t         wpid;
  char          *path;
  int           status;

  if ((pid = fork()) < 0)
    perror("sh");
  if (!pid)
  {
    path = get_path(args, envp);
    if (execve(path,args,envp) == -1)
      perror("sh");
    exit(EXIT_FAILURE);
  }
  else
    waitpid(pid, &status, WUNTRACED);
  return (1);
}




// int       sh_execute(char **args, char **envp)
// {
//   if(!strcmp(args[0],"echo"))
//     return (builtin_echo(args));
//   if(!strcmp(args[0],"cd"))
//     return (builtin_cd(args));
//   if(!strcmp(args[0],"pwd"))
//     return (builtin_pwd());
//   if(!strcmp(args[0],"export"))
//     return (builtin_export(args));
//   if(!strcmp(args[0],"unset"))
//     return (builtin_unset(args));
//   if(!strcmp(args[0],"env"))
//     return (builtin_env(envp));
//   if(!strcmp(args[0],"exit"))
//     return (builtin_exit(args));
//   return sh_launch(args, envp);
// }

// void            sh_loop(char **envp)
// {
//     char *line;
//     char **args;
//     int status;
   
//     status = 1;
//     while (status)
//     {
//         printf("> ");
//         line = sh_read_line();
//         args = sh_split_line(line);

//         status = sh_execute(args,envp);
//         free(line);
//         free(args);
//     }
// }


int           main(int argc, char **argv, char **envp)
{
  char      **envlist;

    if (!(envlist = envList_dup(envp)))
    {
        /*error*/
        return (0);
    }
    p = envlist;
    while (envlist[k])
      printf("%s\n",envlist[k++]);
    printf("\n\n\n%d\n\n\n",k);
    if (!(envlist = addTo_envList(envp,tmp)))
    {
        /*error*/
        return (0);
    }
    k = 0;
    while (envlist[k])
      printf("%s\n",envlist[k++]);
    printf("\n\n\n%d\n\n\n",k);
    clear(p);
    clear(envlist);
    free(p);
    free(envlist);
    //sh_loop(envp);
    return EXIT_SUCCESS;
}