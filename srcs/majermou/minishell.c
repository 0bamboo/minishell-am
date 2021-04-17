#include "./builtins/minishell.h"


int             main(int argc, char **argv, char **envp)
{
  t_envlist    envlist;
  t_cmd_list   command;
  t_cmd_list   command0;
  t_cmd_list   command1;

  command.args = malloc(10 * sizeof(char*));
  command.args[0] = strdup("unset");
  command.args[1] = strdup("PWD");
  command.args[2] = NULL;

  // command0.args = malloc(10 * sizeof(char*));
  // command0.args[0] = strdup("cd");
  // command0.args[1] = NULL;

  command1.args = malloc(10 * sizeof(char*));
  command1.args[0] = strdup("cd");
  command1.args[1] = strdup("..");
  command1.args[2] = NULL;
  
  if (env_varsdup(&envlist,envp))
  {
    printf("---------------------error_0---------------------\n");
    return (1);
  }
  rmfrom_envlist(&envlist, "OLDPWD");

  builtin_env(&envlist);
  printf("\n\n\n\n\n\n\n");
  builtin_unset(&command,&envlist);
  printf("\n\n\n\n\n\n\n");
  builtin_env(&envlist);
  printf("\n\n\n\n\n\n\n");
  builtin_cd(&envlist, &command1);
  printf("\n\n\n\n\n\n\n");
  builtin_env(&envlist);



  // builtin_echo(&command);
  // builtin_exit(&command,0);
  // builtin_cd(&envlist, &command);
  // builtin_exit('h');
  // printf("\n\n\n\n\n\n\n");
  // cleanup(envlist.vars, array_lenght(envlist.vars));
  // cleanup(command.args, array_lenght(command.args));
  // free(envlist.vars);
  // free(command.args);
  return (0);
}