#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

typedef struct          s_cmd_list
{
    char	              **args;
    int		              nbrpipe;
    int                 iterator;
    struct s_cmd_list   *next;
}                       t_cmd_list;

size_t                  ft_strlen(const char *s);
size_t                  ft_strlcpy(char *dst, const char *src, size_t size);


// void            clear(char **arr)
// {
//   int           i;

//   i = 0;
//   while (arr[i])
//     free(arr[i++]);
// }

int             array_lenght(char **arr)
{
  int           lenght;

  lenght = 0;
  while (arr[lenght])
    lenght++;
  return (lenght);
}

unsigned        random_num_generator(int  range)
{
  void          *allocation;
  unsigned      random;

  if (!(allocation = malloc(1)))
    return (range/3);
  random = (unsigned)allocation;
  free(allocation);
  return (random%range);
}

char            **env_vardup(char  **envp)
{
  char          **ret;
  int           i;

  if (!(ret = (char**)malloc((array_lenght(envp) + 1) * sizeof(char*))))
    return (NULL);
  i = 0;
  while (envp[i])
  {
    if (!(ret[i] = (char*)malloc((ft_strlen(envp[i]) + 1) * sizeof(char))))
    {
      //free
      return (NULL);
    }
    ft_strlcpy(ret[i],envp[i],ft_strlen(envp[i]) + 1);
    i++;
  }
  ret[i] = NULL;
  return (ret);
}

char          **addTo_envList(char **envlist, char* new_var)
{
  char        **ret;
  int         i;
  int         random;

  if (!(ret = (char**)malloc(((array_lenght(envlist) + 2) * sizeof(char*)))))
    return (NULL);
  i = 0;
  random = random_num_generator(array_lenght(envlist));
  while (i < random)
  {
    //printf("%d\n",i);
    if (!(ret[i] = (char*)malloc(ft_strlen(envlist[i]) * sizeof(char) + 1)))
    {
      //free
      return (NULL);
    }
    ft_strlcpy(ret[i],envlist[i],ft_strlen(envlist[i]) + 1);
    i++;
  }
  if (!(ret[i] = (char*)malloc(ft_strlen(new_var) * sizeof(char) + 1)))
  {
          //free
      return (NULL);
  }
  ft_strlcpy(ret[i++],new_var,ft_strlen(new_var) + 1);
  while (envlist[i])
  {
    //printf("%d\n",i);
    if (!(ret[i] = (char*)malloc(ft_strlen(envlist[i]) * sizeof(char) + 1)))
    {
      //free
      return (NULL);
    }
    ft_strlcpy(ret[i],envlist[i],ft_strlen(envlist[i]) + 1);
    i++;
  }
  ret[i] = NULL;
  return (ret);
}






int           main(int argc, char **argv, char **envp)
{
	char      **env_vars;
  int       k;
  char      *tmp = strdup("a=abcd");

  if (!(env_vars = env_vardup(envp)))
  {
    /*error*/
    return (0);
  }



  // k = 0;
  // while (env_vars[k])
  // {
  //   printf("%s\n",env_vars[k++]);  
  // }

  if (!(env_vars = addTo_envList(env_vars,tmp)))
  {
    /*error*/
    return (0);
  }

  k = 0;
  while (env_vars[k])
    printf("%s\n",env_vars[k++]);


  //printf("%d\n",random_num_generator(561595));
  //clear(env_vars);
  free(tmp);
  free(env_vars);


  return (0);
}