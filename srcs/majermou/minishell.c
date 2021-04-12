#include "minishell.h"




















int             main(int argc, char **argv, char **envp)
{
  t_cmd_list    command;
  int           k;

  
  if (env_varsdup(&command,envp))
  {
    printf("---------------------error_0---------------------\n");
    return (1);
  }
  k = 0;
  while (command.env_vars[k])
  {
    printf("%d---%s\n",k,command.env_vars[k]);k++;
  }
  printf("\n\n\n\n\n\n\n");

  if (addto_envlist(&command, "A=B"))
  {
    printf("-------------------error_1-----------------------\n");
    return (1);
  }
  k = 0;
  while (command.env_vars[k])
  {
    printf("%d---%s\n",k,command.env_vars[k]);k++;
  }
  printf("\n\n\n\n\n\n\n");


  if (rmfrom_envlist(&command, "A"))
  {
    printf("-------------------error_2-----------------------\n");
    return (1);
  }
  k = 0;
  while (command.env_vars[k])
  {
    printf("%d---%s\n",k,command.env_vars[k]);k++;
  }

  cleanup(command.env_vars,array_lenght(command.env_vars));
  free(command.env_vars);






  // k = 0;
  // while (env_vars[k])
  // {
  //   printf("%s\n",env_vars[k++]);  
  // }

  // if (!(command->env_vars = addto_envlist(command->env_vars,tmp)))
  // {
  //   /*error*/
  //   return (0);
  // }
  //printf("%d\n",random_num_generator(range));
  //clear(env_vars);
  // free(tmp);
  // free(command->env_vars);

  return (0);

}