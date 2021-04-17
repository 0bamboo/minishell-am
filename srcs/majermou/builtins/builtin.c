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

int check_option(char *str)
{
  int   i;

  i = 0;
  if (str[i] != '-')
    return (1);
  while (str[++i])
  {
    if (str[i] != 'n')
      return (1);
  }
  return (0);
}

int builtin_echo(t_cmd_list *cmd)
{
  int   i;
  int   newline;

  i = 1;
  newline = 0;
  while (cmd->args[i] && !check_option(cmd->args[i]))
  {
    newline = 1;
    i++;
  }
  while (cmd->args[i])
  {
    printf("%s",cmd->args[i]);
    if (cmd->args[i + 1])
      printf(" ");
    i++;
  }
  if (!newline)
    printf("\n");
  return (0);
}

int get_val(char *str)
{
  long long   num;
  int         i;
  int         sign;

  num = 0;
  i = 0;
  sign = 1;
  if (str[i] == '-')
    sign = -1;
  while (str[i])
  {
    if (str[i] < 48 || str[i] > 58)
    {
      printf("exit\nbash: exit: %s: numeric argument required\n",str);
      return (255);
    }
    num = num * 10 + (str[i] - '0');
    i++;
  }
  num *= sign; 
  return (num % 256);
}

int   builtin_exit(t_cmd_list *cmd, int status)
{
  int   ret;

  if (!cmd->args[1])
  {
    printf("exit\n");
    exit(status);
  }
  if (cmd->args[2])
  {
    printf("exit\nbash: exit: too many arguments\n");
    return (1);
  }
  exit(get_val(cmd->args[1]));
}