#include "minishell.h"


int             main(int argc, char **argv, char **envp)
{
  t_envlist    envlist;
  t_cmd_list   command;
  t_cmd_list   command0;

  command.args = malloc(6 * sizeof(char*));
  command.args[0] = strdup("cd");
  command.args[1] = strdup(".");
  // command.args[2] = strdup("A=A");
  // command.args[3] = strdup("A=A5345*35");
  // command.args[4] = strdup("A");
  command.args[2] = NULL;
  // command0.args = malloc(9 * sizeof(char*));
  // command0.args[0] = strdup("export");
  // command0.args[1] = NULL;
  
  if (env_varsdup(&envlist,envp))
  {
    printf("---------------------error_0---------------------\n");
    return (1);
  }
  rmfrom_envlist(&envlist, "OLDPWD");

  // builtin_env(&envlist);
  // printf("\n\n\n\n\n\n\n");
  // builtin_export(&command,&envlist);
  // builtin_export(&command0,&envlist);
  // builtin_env(&envlist);
  // printf("\n\n\n\n\n\n\n");
  // builtin_cd(&envlist, &command);
  // builtin_env(&envlist);
  // builtin_exit('h');
  // printf("\n\n\n\n\n\n\n");


  cleanup(envlist.vars, array_lenght(envlist.vars));
  cleanup(command.args, array_lenght(command.args));
  free(envlist.vars);
  free(command.args);

  return (0);
}