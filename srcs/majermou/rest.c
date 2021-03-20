#include "../includes/minishell.h"

char            **sh_split_line(char *line)
{
  int           buffersize;
  int           position;
  char          **tokens;
  char          *token;

  buffersize = SH_TOK_BUFSIZE;
  position = 0;
  if (!(tokens= malloc(buffersize * sizeof(char*))))
  {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }
  token = strtok(line, SH_TOK_DELIM);
  while (token)
  {
    tokens[position] = token;
    position++;

    if (position >= buffersize)
    {
      buffersize += SH_TOK_BUFSIZE;
      if (!(tokens = realloc(tokens, buffersize * sizeof(char*))))
      {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, SH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

char            *sh_read_line()
{
    int         buffersize;
    int         position;
    int         ctr;
    char        *buffer;

    buffersize = SH_RL_BUFSIZE;
    position = 0;
    if (!(buffer = (char*)malloc(sizeof(char) * buffersize)))
    {
        fprintf(stderr, "Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        ctr = getchar();
        if (ctr == EOF || ctr == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = ctr;
        }
        position++;
        if (position >= buffersize)
        {
            buffersize += SH_RL_BUFSIZE;
            if (!(buffer = realloc(buffer, buffersize)))
            {
                fprintf(stderr, "Allocation Error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}