
#include "includes/minishell.h"
#include "srcs/get_next_line.h"
#include "libft/libft.h"


// Example of doubly linked list :

int parse(char *line)
{
    int i;
    int count;
    char c;
    int pos;
    int credir;

    i = 0;
    count = 0;
    // puts("im in");
    while (line[i])
    {
        c = line[i];
        // Check errors of semicolon :
        if (line[i] == ';')
        {
            i++;
            if (line[0] == ';') // if the first chars is semicolon it is an error
                return 1;
            while (line[i])
            {
                // if the char after the semicolon is one of this | or ; then it is an error
                if (line[i] == '|' || line[i] == ';')
                    return 1;
                else if (line[i] == ' ') // skip while it's a white space
                    i++;
                else
                    break; // break if nothing above was executed
            }
            i--;// for knowing the char that we break at .... pardon my english hahaha
        }
        // Check Errors of pipe :
        else if (line[i] == '|') 
        {
            i++;
            // if the first char is pipe or the next one is backslash zero then it is an error
            if (line[0] == '|' || !line[i + 1])
                return 1;
            while (line[i])
            {
                // Skip white spaces :
                if (line[i] == ' ')
                    i++;
                else if (line[i] == '|' || line[i] == ';') // Raise an exception if this condtion true
                    return 1;
                else
                    break;
            }
            i--;
        }
        else if ((line[i] == '>' || line[i] == '<')) // Check errors of redirection :
        {//     return 1;
            credir = 1;
            i++;
            while (line[i])
            {
                // Start counting the redirection > 
                if (c == '>' && line[i] == '>')
                {
                    puts("hi");
                    c = '>';
                    credir += 1;
                    i++;
                }
                else if (line[i + 1] && c == '>' && line[i] == ' ' && line[i + 1] == '>') // This condition for this case for example  > > 
                    return 1;
                else if (line[i] == ' ')
                    i++; // this condition for ; and | after redir | this  for > after < | this for  > or < after < | this for counting the number of redirection >  
                else if (line[i] == ';' || line[i] == '|' || (line[i] == '<' && c == '>') || (c == '<' && (line[i] == '>' || line[i] == '<')) || credir >= 3)
                    return 1;
                else
                    break;
            }
            if (!line[i])
                return 1;
            i--;
        }    // printf("->%c,\t", c);
       else if (c == '"') // Check errors of double quotes :
       {
           i++;
           while (line[i] != c && line[i])
           {
               // if you find backslash skip too chars the current one and the next one :
               if (line[i] == '\\' && line[i + 1] != '\0')
               {
                   i += 2;
                   continue;
               }
               i++;
           }
           if (line[i] != c) // this for checking the double quotes exists : else we raise an exception
           {
               return (1);
           }
       }
       else if (c == '\'') // Check errors of single quotes :
       {
           i++;
           while (line[i] != '\'' && line[i])
               i++;
           if (line[i] != c) // checking that the last chars after loop is single quotes else it is an error
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


    line = NULL;
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