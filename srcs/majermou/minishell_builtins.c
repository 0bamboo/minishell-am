#include "minishell.h"

int builtin_unset(t_cmd_list *cmd, t_envlist *envlist)
{
  int     i;
  int     ret;

  ret = 0;
  i = 1;
  while (cmd->args[i])
  {
    if (!is_valid_id(cmd->args[i]))
    {
      if (rmfrom_envlist(envlist, cmd->args[i]))
        return (1);
    }
    else
    {
      printf("bash: unset: `%s': not a valid identifier\n",cmd->args[i]);
      ret = 1;
    }
    i++;
  }
  return (ret);
}

int builtin_env(t_envlist *envlist)
{
  int     i;
  int     j;

  i = 0;
  j = 0;
  while (envlist->vars[i])
  {
    j = 0;
    while (envlist->vars[i][j] && envlist->vars[i][j] != '=')
      j++;
    if (envlist->vars[i][j])
      printf("%s\n",envlist->vars[i]);
    i++;
  }
  return (0);
}

int builtin_export(t_cmd_list *cmd, t_envlist *envlist)
{
  int   i;
  int   ret;

  i = 1;
  ret = 0;
  while (cmd->args[i])
  {
    if (!is_valid_id(cmd->args[i]))
    {
      if (search_var(envlist, cmd->args[i]) > 0)
      {
        printf("%s\n",cmd->args[i]);
        if (cmd->args[i][lenghtvar(cmd->args[i])])
          replace_var(envlist, search_var(envlist, cmd->args[i]), cmd->args[i]);
      }
      else
        addto_envlist(envlist, cmd->args[i]);
    }
    else
    {
      printf("bash: export: `%s': not a valid identifier\n",cmd->args[i]);
      ret = 1;
    }
    i++;
  }
  if (i == 1)
    builtin_env(envlist);
  //printing_envlist(cmd);
  return (ret);
}




// int             builtin_cd(char **args)
// {
//     chdir(args[1]);
//     return (1);

// int             builtin_pwd(void)
// {
//     char        buf[MAXPATHLEN];

//     printf("%s\n",getcwd(buf,MAXPATHLEN));
//     return (1);
// }

// int             builtin_exit(char **args)
// {
//     int num = ft_atoi(args[0]);
//     exit(num);
// }

// void  printing_envlist(t_cmd_list *cmd)
// {
// }