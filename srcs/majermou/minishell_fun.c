#include "../includes/minishell.h"

void            stringsCopying(char *dst, char *src)
{
  int           i;

  i = 0;
  while (src[i])
  {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
}

size_t		ft_strlen(char *s)
{
	size_t l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

void            clear(char **arr)
{
  int           i;

  i = 0;
  while (arr[i])
    free(arr[i++]);
}

char            **envList_dup(char  **envp)
{
  char          **ret;
  int           i;

  i = 0;
  while (envp[i++]);
  if (!(ret = (char**)malloc(i * sizeof(char*))))
    return (NULL);
  i = 0;
  while (envp[i])
  {
    if (!(ret[i] = (char*)malloc((ft_strlen(envp[i]) + 1) * sizeof(char))))
    {
      //free
      return (NULL);
    }
    stringsCopying(ret[i],envp[i]);
    i++;
  }
  ret[i] = NULL;
  return (ret);
}

char          **addTo_envList(char **envlist, char* new_var)
{
  char        **ret;
  int         i;

  i = 0;
  while (envlist[i++]);
  if (!(ret = (char**)malloc((i + 1) * sizeof(char*))))
    return (NULL);
  i = 0;
  while (envlist[i])
  {
    if (!(ret[i] = (char*)malloc(ft_strlen(envlist[i]) * sizeof(char) + 1)))
    {
      //free
      return (NULL);
    }
    stringsCopying(ret[i],envlist[i]);
    i++;
  }
  if (!(ret[i] = (char*)malloc(ft_strlen(new_var) * sizeof(char) + 1)))
  {
      //free
      return (NULL);
  }
  stringsCopying(ret[i++],new_var);
  ret[i] = NULL;
  return (ret);
}

char            *get_path(char **args, char **envp)
{
  struct stat   buf;
  char          **arr;
  char          *tmp;
  char          *path;
  int           i;

  i = 0;
  while (strncmp(envp[i],"PATH=",5))
    i++;
  arr = ft_split(envp[i] + 5,':');
  i = 0;
  while (arr[i])
  {
    path = ft_strjoin(arr[i++],"/");
    tmp = path;
    path = ft_strjoin(path,args[0]);
    free(tmp);
    if (!stat(path,&buf))
    {
      i = 0;
      while (arr[i])
        free(arr[i++]);
      return (path);
    }
    free(path);
  }
  return (NULL);
}