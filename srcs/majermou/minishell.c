#include "minishell.h"


int             main(int argc, char **argv, char **envp)
{
  t_envlist    envlist;
  t_cmd_list   command;
  t_cmd_list   command0;

  command.args = malloc(9 * sizeof(char*));
  command.args[0] = strdup("export");
  command.args[1] = strdup("A");
  command.args[2] = NULL;
  // command.args[2] = strdup("A=A");
  // command.args[3] = strdup("A=A5345*35");
  // command.args[4] = strdup("A");
  command0.args = malloc(9 * sizeof(char*));
  command0.args[0] = strdup("export");
  command0.args[1] = NULL;
  
  if (env_varsdup(&envlist,envp))
  {
    printf("---------------------error_0---------------------\n");
    return (1);
  }

  // builtin_env(&envlist);
  // printf("\n\n\n\n\n\n\n");
  builtin_export(&command,&envlist);
  builtin_export(&command0,&envlist);
  printf("\n\n\n\n\n\n\n");
  // builtin_env(&envlist);
  // printf("\n\n\n\n\n\n\n");


  cleanup(envlist.vars, array_lenght(envlist.vars));
  cleanup(command.args, array_lenght(command.args));
  cleanup(command0.args, array_lenght(command.args));
  free(envlist.vars);
  free(command.args);
  free(command0.args);

  return (0);
}