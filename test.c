
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


// #include<stdio.h>
// #include<stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <unistd.h>


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


void _add_to_string(char *buff, int index, char *fill, int size)
{
    int i;

    // i = strlen(buff);
    // printf("index of start == |%d|,\n", index);
    // printf("size == |%d|, \n", size);
    // printf("first char of fill = |%c|\n", *fill);
    // printf("buff[%d]indx - 1 == |%c|\n", index-1, buff[index-1]);
    // printf("buff[%d]indx     == |%c|\n", index, buff[index]);
    while (*fill && size > 0)
    {
        // printf("|%c|\t,", *fill);
        buff[index++] = *fill++;
        size--;
    }
    // puts("");
}


int _line_counter_(char *buffer)
{
    int i;
    int counter;
    char *tmp;
    int j;
    int count;
    char *fill;

    i = -1;
    counter = 0;
    while (buffer[++i])
    {
        if (buffer[i] == '$' && buffer[i + 1] == '?')
        {
            i++;
            counter++;
        }
        else if (buffer[i] == '$' && ft_isdigit(buffer[i + 1]))
        {
            if (buffer[++i] == 48)
            {
                counter += 4;
                i++;
            }
            else
                i++;
            
        }
        else if (buffer[i] == '$' && !(_is_special_(buffer[i + 1])))
        {
            count = 0;
            j = ++i;
            while (!(_is_special_(buffer[j])) && buffer[j++])
                count++;
            tmp = (char *)malloc(sizeof(char) * (count + 1));
            j = 0;
            while (!(_is_special_(buffer[i])) && buffer[i])
                tmp[j++] = buffer[i++];
            tmp[j] = '\0';
            fill = getenv(tmp);
            if (fill)
                counter += ft_strlen(fill);
            if (tmp)
            {    
                free(tmp);
                tmp = NULL;
            }
            i--;
            continue;
        }
        else if (buffer[i] == '"')
        {
            counter++;
            i++;
            while (buffer[i] != '"' && buffer[i])
            {
                if (buffer[i] == '$' && ft_isdigit(buffer[i + 1]))
                {
                    if (buffer[++i] == 48)
                    {
                        i++;
                        counter += 4;
                    }
                    else
                        i++;
                    
                }
                else if (buffer[i] == '\\')
                {
                    i += 2;
                    counter += 2;
                }
                else if (buffer[i] == '$' && !(_is_special_(buffer[i + 1])))
                {
                    count = 0;
                    j = ++i;
                    while (!(_is_special_(buffer[j])) && buffer[j++])
                        count++;
                    tmp = (char *)malloc(sizeof(char) * (count + 1));
                    j = 0;
                    while (!(_is_special_(buffer[i])) && buffer[i])
                        tmp[j++] = buffer[i++];
                    tmp[j] = '\0';
                    fill = getenv(tmp);
                    if (fill)
                    {
                        counter += ft_strlen(fill);
                    }
                    if (tmp)
                    {
                        free(tmp);
                        tmp = NULL;
                    }
                }
                else
                {
                    counter++;
                    i++;
                }
            }
        }
        else if (buffer[i] == '\'')
        {
            i++;
            counter++;
            while (buffer[i] && buffer[i] != '\'')
            {    
                i++;
                counter++;
            }
        }
        if (buffer[i])
            counter++;
    }
    return counter;
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
    int counter;

    i = -1;
    g = 0;
    counter = 0;
    // This allocation is just for testing , but in the real project i need to calculate,
    //how much memory i will use first before changing the value of env variables.
    // printf("line counter = [%d]\n", _line_counter_(buffer));
    counter = _line_counter_(buffer);
    printf("length = %d\n", counter);
    global = (char *)malloc(sizeof(char *) * (counter + 1));
    while (buffer[++i])
    {
        // Fisrt i will check for the $ var and the special character ? cuz the output of this one is different than usual,
        // the executer will handle this one, for me i will just skip this one and send it to him ... tjdert agmano mohmaaad hhhh
        if (buffer[i] == '$' && buffer[i + 1] == '?')
        {
            global[g++] = buffer[i++];
            // counter++;
            // printf("$?global == 0 === |%lu| |%d|\n", strlen(global), counter);
        }
        else if (buffer[i] == '$' && ft_isdigit(buffer[i + 1]))
        {
            // This one is when i found the $ var again and numbers after it,
            // so for zero i will print the name of shell,
            // and for other numbers i will skip the first one and print every char next to it, 
            if (buffer[++i] == 48)
            {
                _add_to_string(global, g, "bash", 4);
                g +=4;
                // counter += 4;
                // printf("0global == 0 === |%lu| |%d|\n", strlen(global), counter);
                i++;
            }
            else
            {
                counter++;
                i++;
            }
            
        }
        else if (buffer[i] == '$' && !(_is_special_(buffer[i + 1])))
        {
            // This case is when i found $ char again and no special char next to it, so i need to get that string after that dollar char....
            count = 0;
            j = ++i;
            counter++;
            // printf("first char = |%c|\n", buffer[i]);
            
            // This loop is for counting the length of the string that i will look for its real value in envs vars....
            while (!(_is_special_(buffer[j])) && buffer[j++])
                count++;
            // Allocate the string 
            tmp = (char *)malloc(sizeof(char) * (count + 1));
            j = 0;

            // Copy the string into tmp var....
            while (!(_is_special_(buffer[i])) && buffer[i])
            {
                tmp[j++] = buffer[i++];
            }
            tmp[j] = '\0';
            // printf("tmp = |%s|\n", tmp);
            // i--;

            // Look for the real value of that string using the function getenv...
            fill = getenv(tmp);
            // printf("fill = |%s|\n", fill);
            if (fill)
            {
                // If i did found the env value for that string then i will concatenate it with the global string 
                count = ft_strlen(fill);
                // counter += count;
                _add_to_string(global, g, fill, count);
                g += count;
                // This one for moving the index of global string...
            }
            if (tmp)
            {    
                // Freeing the tmp string
                free(tmp);
                tmp = NULL;
            }
            i--;
            // printf("$global == 0 === |%lu| |%d|\n", strlen(global), counter);
            counter--;
            // printf("buffer[%d] = %c\n", i, buffer[i]);
            continue;
        }
        else if (buffer[i] == '"')
        {
            // This is another case when i found the dq " char i need to check for backslashes....
            global[g++] = buffer[i++]; // copy the dq var
            // counter++;
            while (buffer[i] != '"' && buffer[i])
            {
                // Loop throw the string inside dq..
                // i++;
                // printf("before = [%c]\n", buffer[i]);
                if (buffer[i] == '$' && ft_isdigit(buffer[i + 1]))
                {
                    // The same case when i found digits after dollar char...
                    if (buffer[++i] == 48)
                    {
                        _add_to_string(global, g, "bash", 4);
                        g +=4;
                        i++;
                        // counter += 4;
                        // printf("dq$0global == 0 === |%lu| |%d|\n", strlen(global), counter);
                    }
                    else
                    {
                        counter++;
                        i++;
                    }
                    
                }
                else if (buffer[i] == '\\')
                {
                    // This case is one i found the backslash so i need to copy and skip two chars the current one and the next one,
                    // This algorithm will help me for skipping the $var if the number of backslashes is odd and looking for $var if the number of bs is even...
                    // printf("|%d| = |%c|\n", i, buffer[i]);
                    global[g++] = buffer[i++];
                    // printf("|%d| = |%c|\n", i, buffer[i]);
                    global[g++] = buffer[i++];
                    // counter += 2;
                    // printf("bsglobal == 0 === |%lu| |%d|\n", strlen(global), counter);
                    // printf("backslash = [%d] = [%c] | [%d] = [%c] \n", i-1, buffer[i - 1], i, buffer[i]);
                }
                else if (buffer[i] == '$' && !(_is_special_(buffer[i + 1])))
                {
                    // Same thing when you found the $var...
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
                        // counter += count;
                        _add_to_string(global, g, fill, count);
                        g += count;
                    }
                    if (tmp)
                    {
                        // printf("tmp === > |%s|\n", tmp);
                        // printf("fill == > |%s|\n", fill);
                        free(tmp);
                        tmp = NULL;
                    }
                    // printf("dq$global == 0 === |%lu| |%d|\n", strlen(global), counter);

                    // printf("buffer[%d] = %c\n", i, buffer[i]);
                    // continue;
                }
                else
                {
                    // Copy the  other chars of inside dq "" ...
                    // printf("---> |%c|\n", buffer[i]);
                    // counter++;
                    global[g++] = buffer[i++];
                    // printf("dq chars global == 0 === |%lu| |%d|\n", strlen(global), counter);
                }
            }
            // if (buffer[i])
            // {
            //     // Copy the last dq "
            //     // printf("--> |%c|\n", buffer[i]);
                counter++;
            //     global[g++] = buffer[i++];
                // printf("dq allaho a3lam global == 0 === |%lu| |%d|\n", strlen(global), counter);
            //     // printf("--> |%c|\n", buffer[i]);
            // }
            // continue; // why you used this ///never mind hhhhh // no you need to mind
        }
        else if (buffer[i] == '\'')
        {
            global[g++] = buffer[i++];
            // counter++;
            while (buffer[i] && buffer[i] != '\'')
            {    
                global[g++] = buffer[i++];
                // counter++;
            }
            // puts("im out ");
        }
        // Copy the other chars of the string
        global[g++] = buffer[i];
        // counter++;
        // printf(" out global == 0 === |%lu| |%d|\n", strlen(global), counter);
    }
    global[g] = '\0';
    // printf("this global array : |%s|\n", global);
    // printf("----> counter = |%d|\n", counter);
    // printf("global = |%s|\n", global);
    return global;
}


int main()
{
    char *line;
    int checker;
    char *tmp;
    size_t bufsize = 1;
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
        // printf("line = |%s|\n", line);
        // printf("line length = |%lu|\n", strlen(line));
        tmp = _get_env_var_(line);
        printf("tmp length = |%lu|\n", strlen(tmp));
        printf("tmp after editing = |%s|\n", tmp);
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