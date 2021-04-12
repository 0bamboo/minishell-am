#include "minishell.h"

int builtin_unset(t_cmd_list *cmd)
{
  int     i;
  int     ret;

  ret = 0;
  i = 1;
  while (cmd->args[i])
  {
    if (!is_valid_id(cmd->args[i]))
    {
      if (rmfrom_envlist(cmd, cmd->args[i]))
        return (1);
    }
    else
    {
      printf("unset: `%s': not a valid identifier\n",cmd->args[i]);
      ret = 1;
    }
    i++;
  }
  return (ret);
}

int builtin_export(t_cmd_list *cmd)
{
  int   i;
  int   ret;

  i = 1;
  ret = 0;
  while (cmd->args[i])
  {
    if (!is_valid_id(cmd->args[i]))
    {
      if (search_var(cmd, cmd->args[i]) > 0)
      {
        if (cmd->args[i][search_equalkey(cmd->args[i])])
        {
          if (replace_var(cmd,search_var(cmd, cmd->args[i]),cmd->args[i]))
            return (1);
        }
      }
      else
        if (addto_envlist(cmd, cmd->args[i]))
          return (1);
    }
    else
    {
      printf("export: `%s': not a valid identifier\n",cmd->args[i]);
      ret = 1;
    }
    i++;
  }
  if (i == 1)
    builtin_env(cmd);
  //printing_envlist(cmd);
  return (ret);
}

int builtin_env(t_cmd_list *cmd)
{
  int     i;

  i = 0;
  while (cmd->env_vars[i])
  {
    if (cmd->env_vars[i][search_equalkey(cmd->env_vars[i])])
      printf("%s\n",cmd->env_vars[i]);
    i++;
  }
  return (0);
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