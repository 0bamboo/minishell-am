#include "minishell.h"

int             builtin_pwd(void)
{
  char        *buf;

  buf = malloc((MAXPATHLEN + 1) * sizeof(char));
  if (!buf)
    return (1);
  printf("%s\n",getcwd(buf,MAXPATHLEN));
  free(buf);
  return (0);
}

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
  char  *tmp;
  int   j;

  i = 1;
  ret = 0;
  while (cmd->args[i])
  {
    if (!is_valid_id0(cmd->args[i]))
      insert_var(envlist, cmd->args[i]);
    else
    {
      printf("bash: export: `%s': not a valid identifier\n",cmd->args[i]);
      ret = 1;
    }
    i++;
  }
  if (i == 1)
    print_envlist(envlist);
  return (ret);
}

int         print_envlist(t_envlist *envlist)
{
  char      **arr;
  int       i;

  arr = malloc((array_lenght(envlist->vars) + 1) * sizeof(char *));
  if (!arr)
    return (1);
  i = 0;
  while (envlist->vars[i])
  {
    str_copying(arr, envlist->vars[i], i);
    i++;
  }
  arr[i] = NULL;
  //sorting
  printing(arr);
  cleanup(arr,array_lenght(arr));
  free(arr);
  return (0);
}

void  printing(char **arr)
{
  int   i;
  int   j;

  i = 0;
  while (arr[i])
  {
    printf("declare -x ");
    j = 0;
    while (arr[i][j] && arr[i][j] != '=')
    {
      printf("%c",arr[i][j]);
      j++;
    }
    if (arr[i][j])
    {
      printf("=\"");
      printf("%s", arr[i] + ++j);
      printf("\"");
    }
    printf("\n");
    i++;
  }
}























int             builtin_cd(t_envlist *envlist, t_cmd_list *cmd)
{
  char          *path;
  char    *tmp;
  int     i;

  chdir(cmd->args[1]);
  i = 0;
  while (envlist->vars[i])
  {
    if (!ft_strcmp(envlist->vars[i], "PWD")
		|| !ft_strncmp(envlist->vars[i], "PWD=", 4))
      break;
    i++;
	}
  tmp = ft_strjoin("OLD",envlist->vars[i]);
  free(envlist->vars[i]);
  envlist->vars[i] = tmp;
  tmp = ft_strjoin("PID=",path);
  addto_envlist(envlist, tmp);
  free(tmp);
  return (0);
}