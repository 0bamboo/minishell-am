
#include "includes/minishell.h"
#include "srcs/get_next_line.h"
#include "libft/libft.h"


// typedef struct err
// {
//     int er;
//     int i;
//     int credir;
//     char tmp;
// }err;

// // Example of doubly linked list :
// int _check_semi_colon(char *line, err *prs)
// {
//     prs->i++;
//     if (line[0] == ';') // if the first chars is semicolon it is an error
//     {
//         prs->er = 1;
//         return prs->i;
//     }
//     while (line[prs->i])
//     {
//         // if the char after the semicolon is one of this | or ; then it is an error
//         if (line[prs->i] == '|' || line[prs->i] == ';')
//         {
//             prs->er = 1;
//             break;
//         }
//         else if (line[prs->i] == ' ') // skip while it's a white space
//             prs->i++;
//         else
//             break; // break if nothing above was executed
//     }
//     return(--prs->i);// for knowing the char that we break at .... pardon my english hahaha
// }

// int _check_pipe(char *line, err *prs)
// {
//     prs->i++;
//                 // if the first char is pipe or the next one is backslash zero then it is an error
//     if (line[0] == '|' || !line[prs->i + 1])
//     {
//         prs->er = 1;
//         return prs->i;
//     }
//     while (line[prs->i])
//     {
//         // Skip white spaces :
//         if (line[prs->i] == ' ')
//             prs->i++;
//         else if (line[prs->i] == '|' || line[prs->i] == ';') // Raise an exception if this condtion true
//         {
//             prs->er = 1;
//             break;
//         }
//         else
//             break;
//     }
//     return (--prs->i);
// }

// int _check_redirection(char *line, err *prs)
// {
//     prs->credir = 1;
//     prs->i++;
//     while (line[prs->i])
//     {
//         // Start counting the redirection > 
//         if (prs->tmp == '>' && line[prs->i] == '>')
//         {
//             puts("hi");
//             prs->tmp = '>';
//             prs->credir += 1;
//             prs->i++;
//         }
//         else if (line[prs->i + 1] && prs->tmp == '>' && line[prs->i] == ' ' && line[prs->i + 1] == '>') // This condition for this case for example  > > 
//         {
//             prs->er = 1;
//             return prs->i;
//         }
//         else if (line[prs->i] == ' ')
//             prs->i++; // this condition for ; and | after redir | this  for > after < | this for  > or < after < | this for counting the number of redirection >  
//         else if (line[prs->i] == ';' || line[prs->i] == '|' || (line[prs->i] == '<' && prs->tmp == '>') || (prs->tmp == '<' && (line[prs->i] == '>' || line[prs->i] == '<')) || prs->credir >= 3)
//         {
//             prs->er = 1;
//             return prs->i;
//         }
//         else
//             break;
//     }
//     if (!line[prs->i])
//         prs->er = 1;
//     return (--prs->i);
// }

// int _check_double_quotes(char *line, err *prs)
// {
//     prs->i++;
//     while (line[prs->i] != prs->tmp && line[prs->i])
//     {
//         // if you find backslash skip too chars the current one and the next one :
//         if (line[prs->i] == '\\' && line[prs->i + 1] != '\0')
//         {
//             prs->i += 2;
//             continue;
//         }
//         prs->i++;
//     }
//     if (line[prs->i] != prs->tmp) // this for checking the double quotes exists : else we raise an exception
//         prs->er = 1; 
//     return prs->i;
// }

// int _check_single_quotes(char *line, err *prs)
// {
//     prs->i++;
//     while (line[prs->i] != '\'' && line[prs->i])
//         prs->i++;
//     printf("|%c|\n", line[prs->i]);
//     if (line[prs->i] != prs->tmp) // checking that the last chars after loop is single quotes else it is an error
//         prs->er = 1;
//     return prs->i;
// }

// int parse(char *line, err *prs)
// {
//     int i;
//     int count;
//     char c;
//     int pos;
//     int credir;

//     prs->i = 0;
//     count = 0;
//     // puts("im in");
//     prs->er = 0;
//     while (line[prs->i])
//     {
//         prs->tmp = line[prs->i];
//         // Check errors of semicolon :
//         if (line[prs->i] == ';')
//         {
//             prs->i = _check_semi_colon(line, prs);
//             // if (prs->er)
//             //     return 1;
//             // i++;
//             // if (line[0] == ';') // if the first chars is semicolon it is an error
//             //     return 1;
//             // while (line[prs->i])
//             // {
//             //     // if the char after the semicolon is one of this | or ; then it is an error
//             //     if (line[prs->i] == '|' || line[prs->i] == ';')
//             //         return 1;
//             //     else if (line[prs->i] == ' ') // skip while it's a white space
//             //         prs->i++;
//             //     else
//             //         break; // break if nothing above was executed
//             // }
//             // prs->i--;// for knowing the char that we break at .... pardon my english hahaha
//         }
//         // Check Errors of pipe :
//         else if (line[prs->i] == '|') 
//         {
//             prs->i = _check_pipe(line, prs);
//             // if (prs->er)
//             //     return 1;
//             // // if the first char is pipe or the next one is backslash zero then it is an error
//             // if (line[0] == '|' || !line[prs->i + 1])
//             //     return 1;
//             // while (line[prs->i])
//             // {
//             //     // Skip white spaces :
//             //     if (line[prs->i] == ' ')
//             //         prs->i++;
//             //     else if (line[prs->i] == '|' || line[prs->i] == ';') // Raise an exception if this condtion true
//             //         return 1;
//             //     else
//             //         break;
//             // }
//             // prs->i--;
//         }
//         else if ((line[prs->i] == '>' || line[prs->i] == '<')) // Check errors of redirection :
//         {//     return 1;
//             // prs->credir = 1;
//             // prs->i++;
//             // while (line[prs->i])
//             // {
//             //     // Start counting the redirection > 
//             //     if (c == '>' && line[prs->i] == '>')
//             //     {
//             //         puts("hi");
//             //         c = '>';
//             //         prs->credir += 1;
//             //         prs->i++;
//             //     }
//             //     else if (line[prs->i + 1] && c == '>' && line[prs->i] == ' ' && line[prs->i + 1] == '>') // This condition for this case for example  > > 
//             //         return 1;
//             //     else if (line[prs->i] == ' ')
//             //         prs->i++; // this condition for ; and | after redir | this  for > after < | this for  > or < after < | this for counting the number of redirection >  
//             //     else if (line[prs->i] == ';' || line[prs->i] == '|' || (line[prs->i] == '<' && c == '>') || (c == '<' && (line[prs->i] == '>' || line[prs->i] == '<')) || prs->credir >= 3)
//             //         return 1;
//             //     else
//             //         break;
//             // }
//             // if (!line[prs->i])
//             //     return 1;
//             // prs->i--;
//             prs->i = _check_redirection(line, prs);
//             printf("|-%d-|\n", prs->er);
//             // if (prs->er)
//             //     return 1;
//         }    // printf("->%c,\t", c);
//        else if (prs->tmp == '"') // Check errors of double quotes :
//        {
//            prs->i = _check_double_quotes(line, prs);
//            printf("|%c|\n", line[prs->i]);
//         //    if (prs->er)
//         //         return 1;
//         //    puts("im in");
//         //    while (line[prs->i] != prs->tmp && line[prs->i])
//         //    {
//         //        // if you find backslash skip too chars the current one and the next one :
//         //        if (line[prs->i] == '\\' && line[prs->i + 1] != '\0')
//         //        {
//         //            prs->i += 2;
//         //            continue;
//         //        }
//         //        prs->i++;
//         //    }
//         //    if (line[prs->i] != prs->tmp) // this for checking the double quotes exists : else we raise an exception
//         //    {
//         //        return (1);
//         //    }
//        }
//        else if (prs->tmp == '\'') // Check errors of single quotes :
//        {
//            prs->i = _check_single_quotes(line, prs);
//         //    if (prs->er)
//         //         return 1;
//         //    prs->i++;
//         //    while (line[prs->i] != '\'' && line[prs->i])
//         //        prs->i++;
//         //     printf("|%c|\n", line[prs->i]);
//         //    if (line[prs->i] != prs->tmp) // checking that the last chars after loop is single quotes else it is an error
//         //    {
//         //        return (1);
//         //    }
//        }
//         if (prs->er)
//             return 1;
//        prs->i++;
//     }
//     return (0);
// }


#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>


// Example of doubly linked list :
// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	int		len;
// 	char	*tmp;

// 	i = 0;
// 	len = strlen(s);
// 	if (!(tmp = (char *)malloc(len + 1)))
// 		return (0);
// 	while (i <= len)
// 	{
// 		tmp[i] = s[i];
// 		i++;
// 	}
// 	return (tmp);
// }


int     _is_special_(char c)
{
    if ((c >= 32 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || ((c >= 123 && c <= 126)) || c == '\0')
        return 1;
    return 0;
}


void _add_to_string(char *buff, char *fill, int size)
{
    int i;

    i = strlen(buff);
    while (*fill && size > 0)
    {
        buff[i++] = *fill++;
        size--;
    }
}


char *_get_env_var_(char *buffer)
{
    int i;
    int j;
    int count;
    char *tmp;
    char *fill;
    int g;
    char *global;

    i = -1;
    g = 0;
    global = (char *)malloc(sizeof(char *) * 100);
    while (buffer[++i])
    {
        if (buffer[i] == '$' && buffer[i + 1] == '?')
            global[g++] = buffer[i++];
        else if (buffer[i] == '$' && ft_isdigit(buffer[i + 1]))
        {
            if (buffer[++i] == 48)
            {
                _add_to_string(global + g, "bash", 4);
                g +=4;
                i++;
            }
            else
                i++;
            
        }
        else if (buffer[i] == '$' && !(_is_special_(buffer[i + 1])))
        {
            count = 0;
            j = ++i;
            // printf("first char = |%c|\n", buffer[i]);
            while (!(_is_special_(buffer[j])) && buffer[j++])
                count++;
            tmp = (char *)malloc(sizeof(char) * (count + 1));
            j = 0;
            while (!(_is_special_(buffer[i])) && buffer[i])
            {
                tmp[j++] = buffer[i++];
            }
            puts("hello");
            tmp[j] = '\0';
            // printf("tmp = |%s|\n", tmp);
            // i--;
            fill = getenv(tmp);
            // printf("fill = |%s|\n", fill);
            if (fill)
            {
                count = ft_strlen(fill);
                _add_to_string(global + g, fill, count);
                g += count;
            }
            i--;
            // printf("buffer[%d] = %c\n", i, buffer[i]);
            continue;
        }
        else if (buffer[i] == '"' && !(_is_special_(buffer[i + 1])))
        {
            global[g++] = buffer[i++];
            while (buffer[i] != '"' && buffer[i])
            {
                // i++;
                // printf("before = [%c]\n", buffer[i]);
                if (buffer[i] == '$' && ft_isdigit(buffer[i + 1]))
                {
                    if (buffer[++i] == 48)
                    {
                        _add_to_string(global + g, "bash", 4);
                        g +=4;
                        i++;
                    }
                    else
                        i++;
                    
                }
                else if (buffer[i] == '\\')
                {
                    global[g++] = buffer[i++];
                    global[g++] = buffer[i++];
                    // printf("backslash = [%d] = [%c] | [%d] = [%c] \n", i-1, buffer[i - 1], i, buffer[i]);
                    // continue;
                }
                else if (buffer[i] == '$')
                {
                    count = 0;
                    j = ++i;
                    // printf("first char = |%c|\n", buffer[i]);
                    while (!(_is_special_(buffer[j])) && buffer[j++])
                        count++;
                    tmp = (char *)malloc(sizeof(char) * (count + 1));
                    j = 0;
                    while (!(_is_special_(buffer[i])) && buffer[i])
                    {
                        tmp[j++] = buffer[i++];
                    }
                    tmp[j] = '\0';
                    // i--;
                    fill = getenv(tmp);
                    if (fill)
                    {
                        count = ft_strlen(fill);
                        _add_to_string(global + g, fill, count);
                        g += count;
                    }
                    // i--;

                    // printf("buffer[%d] = %c\n", i, buffer[i]);
                    // continue;
                }
                else
                    global[g++] = buffer[i++];

            }
            if (buffer[i])
                global[g++] = buffer[i++];
            continue;
        }
        global[g++] = buffer[i];
    }
    global[g] = '\0';
    // printf("global = |%s|\n", global);
    return global;
}


int main()
{
    char *line;
    int checker;
    char *tmp;
    size_t bufsize = 32;
    size_t r;
    // err prs;


    line = NULL;
    char *tmpp;
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
        printf("line = |%s|\n", line);
        printf("line length = |%lu|\n", strlen(line));
        tmp = _get_env_var_(line);
        printf("tmp after editing = |%s|\n", tmp);
        printf("tmp length = |%lu|\n", strlen(tmp));
        // _start_parsing(line, prs, &head);
        free(line);
        free(tmp);
        tmp = NULL;
        line = NULL;
        write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    }
    // checker = check_special_(buffer);
    return(0);
}