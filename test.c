
#include "includes/minishell.h"
#include "srcs/get_next_line.h"
#include "libft/libft.h"


// Example of doubly linked list :

int parse(char *line)
{
    int i;
    int count;
    char c;
    int credir;

    i = 0;
    count = 0;
    // puts("im in");
    while (line[i])
    {
        c = line[i];
        if ((line[i] == '>' || line[i] == '<'))
        {//     return 1;
            i++;
            credir = 1;
            while (line[i])
            {
                // c = line[i];
                if (line[i] == '>' && c == '>')
                {
                    c = '>';
                    credir += 1;
                    i++;
                }
                else if (line[i] == ' ')
                    i++;
                else if (line[i] == ';' || line[i] == '|' || (line[i] == '<' && c == '>') || (c == '<' && (line[i] == '>' || line[i] == '<')) || credir >= 3)
                    return 1;
                else
                    break;
            }
            i--;
        }    // printf("->%c,\t", c);
       else if (c == '"')
       {
           i++;
           while (line[i] != c && line[i])
           {
               if (line[i] == '\\' && line[i + 1] != '\0')
               {
                   i += 2;
                   continue;
               }
               i++;
           }
           if (line[i] != c)
           {
               return (1);
           }
       }
       else if (c == '\'')
       {
           i++;
           while (line[i] != '\'' && line[i])
               i++;
           if (line[i] != c)
           {
               return (1);
           }
       }
       i++;
    }
    return (0);
}

int main()
{
    char *line;
    int checker;
    char *tmp = "";
    size_t bufsize = 32;
    size_t r;

    // printf("|%s| |%s|", NULL, tmp);
    // char *getenv(const char *name);
    // buffer = getenv("CPATH");
    // buffer = (char *)malloc(bufsize * sizeof(char));
    // characters = getline(&buffer,&bufsize,stdin);
    line = NULL;
    // r = get_next_line(0, &buffer);
        write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    while(get_next_line(0, &line) > 0)
    {
        // add_to_history(line, prs);
        // head = malloc(sizeof(p_list));
        // head = NULL;
        if (!strcmp(line, "exit"))
        {
            free(line);
            line = NULL;
            exit(0);
        }
        checker = parse(line);
        printf("--> %d\n", checker);
        printf("|%s|\n", line);
        // _start_parsing(line, prs, &head);
        free(line);
        line = NULL;
        write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    }
    // checker = check_special_(buffer);
    return(0);
}