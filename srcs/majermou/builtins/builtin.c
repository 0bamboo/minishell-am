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


// int       builtin_exit(int ret)
// {
//   exit(ret);
// }

// int       builtin_echo(t_cmd_list *cmd)
// {
//   int   i;
// }