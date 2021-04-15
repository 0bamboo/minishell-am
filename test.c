
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
//     prs->prs->i++;
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

typedef struct sc
{
    char *buffer;
    int i;
    char *fill;
    char *tmp;
    int count;
    int counter;
    int j;
    char *global;
    int g;
    int status;

} prs;


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

static int	ft_len_nbr(long n)
{
	int		size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*ptr;
	int		i;
	long	a;

	a = n;
	if (a == 0)
		return (ft_strdup("0"));
	len = ft_len_nbr(a);
	i = len - 1;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (a < 0)
	{
		ptr[0] = '-';
		a *= -1;
	}
	while (a)
	{
		ptr[i--] = (a % 10) + '0';
		a /= 10;
	}
	ptr[len] = '\0';
	return (ptr);
}

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

void _count_dollar_digits_(prs *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        prs->counter += 4;
        prs->i++;
    }
    else
        prs->i++;
}

void _count_env_vars_(prs *prs)
{
    int count;
    int j;
    char *fill;
    char *tmp;

    count = 0;
    j = ++prs->i;
    while (!(_is_special_(prs->buffer[j])) && prs->buffer[j++])
        count++;
    tmp = (char *)malloc(sizeof(char) * (count + 1));
    j = 0;
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
        tmp[j++] = prs->buffer[prs->i++];
    tmp[j] = '\0';
    fill = getenv(tmp);
    if (fill)
        prs->counter += ft_strlen(fill);
    if (tmp)
    {    
        free(tmp);
        tmp = NULL;
    }
    prs->i--;
}

void _dq_count_env_vars_(prs *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    while (!(_is_special_(prs->buffer[prs->j])) && prs->buffer[prs->j++])
        prs->count++;
    prs->tmp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
        prs->tmp[prs->j++] = prs->buffer[prs->i++];
    prs->tmp[prs->j] = '\0';
    prs->fill = getenv(prs->tmp);
    if (prs->fill)
        prs->counter += ft_strlen(prs->fill);
    if (prs->tmp)
    {
        free(prs->tmp);
        prs->tmp = NULL;
    }
}

void _dq_count_dollar_digits_(prs *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        prs->i++;
        prs->counter += 4;
    }
    else
        prs->i++;
}

void _count_inside_dq_(prs *prs)
{
    prs->counter++;
    prs->i++;
    while (prs->buffer[prs->i] != '"' && prs->buffer[prs->i])
    {
        if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
            _dq_count_dollar_digits_(prs);
        else if (prs->buffer[prs->i] == '\\')
        {
            prs->i += 2;
            prs->counter += 2;
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
            _dq_count_env_vars_(prs);
        else if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
        {
            prs->i += 2;
            prs->counter += strlen(ft_itoa(prs->status));
        }
        else
        {
            prs->counter++;
            prs->i++;
        }
    }
}

void _count_inside_sq_(prs *prs)
{
    prs->i++;
    prs->counter++;
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
    {    
        prs->i++;
        prs->counter++;
    }
}


int _line_counter_(prs *prs)
{
    prs->i = -1;
    prs->counter = 0;
    // prs->buffer = buffer;
    while (prs->buffer[++prs->i])
    {
        if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
        {
            printf("line counter = |%c|\n", prs->buffer[prs->i]);
            prs->i += 1;
            // prs->counter++;
            prs->counter += strlen(ft_itoa(prs->status));
            continue;
        }
        else if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
        {
            _count_dollar_digits_(prs);
            prs->i--;
            continue;
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
        {
            _count_env_vars_(prs);
            continue;
        }
        else if (prs->buffer[prs->i] == '"')
            _count_inside_dq_(prs);
        else if (prs->buffer[prs->i] == '\'')
            _count_inside_sq_(prs);
        if (prs->buffer[prs->i])
            prs->counter++;
    }
    return prs->counter;
}


void    _copy_dollar_digits_(prs *prs)
{
    if (prs->buffer[++prs->i] == 48)
    {
        _add_to_string(prs->global, prs->g, "bash", 4);
        prs->g +=4;
        prs->i++;
    }
    else
        prs->i++; // i think you don't need to do this anyway test it and find out......
}

void _copy_env_vars_(prs *prs)
{
    prs->count = 0;
    prs->j = ++prs->i;
    // counter++;
    // printf("first char = |%c|\n", prs->buffer[prs->i]);
    
    // This loop is for counting the length of the string that prs->i will look for its real value in envs vars....
    while (!(_is_special_(prs->buffer[prs->j])) && prs->buffer[prs->j++])
        prs->count++;
    // Allocate the string 
    prs->tmp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;

    // Copy the string into prs->tmp var....
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
    {
        prs->tmp[prs->j++] = prs->buffer[prs->i++];
    }
    prs->tmp[prs->j] = '\0';
    // printf("prs->tmp = |%s|\n", prs->tmp);
    // prs->i--;

    // Look for the real value of that string using the function getenv...
    prs->fill = getenv(prs->tmp);
    // printf("prs->fill = |%s|\n", prs->fill);
    if (prs->fill)
    {
        // If prs->i did found the env value for that string then prs->i will concatenate it with the prs->global string 
        prs->count = ft_strlen(prs->fill);
        // counter += prs->count;
        _add_to_string(prs->global, prs->g, prs->fill, prs->count);
        prs->g += prs->count;
        // This one for moving the index of prs->global string...
    }
    if (prs->tmp)
    {    
        // Freeing the prs->tmp string
        free(prs->tmp);
        prs->tmp = NULL;
    }
    prs->i--;
}

void _dq_copy_dollar_digits_(prs *prs)
{
    // The same case when prs->i found digits after dollar char...
    if (prs->buffer[++prs->i] == 48)
    {
        _add_to_string(prs->global, prs->g, "bash", 4);
        prs->g +=4;
        prs->i++;
    }
    else
        prs->i++;
}

void    _dq_copy_env_vars_(prs *prs)
{
    // Same thing when you found the $var...
    prs->count = 0;
    prs->j = ++prs->i;
    while (!(_is_special_(prs->buffer[prs->j])) && prs->buffer[prs->j++])
        prs->count++;
    prs->tmp = (char *)malloc(sizeof(char) * (prs->count + 1));
    prs->j = 0;
    while (!(_is_special_(prs->buffer[prs->i])) && prs->buffer[prs->i])
        prs->tmp[prs->j++] = prs->buffer[prs->i++];
    prs->tmp[prs->j] = '\0';
    prs->fill = getenv(prs->tmp);
    if (prs->fill)
    {
        prs->count = ft_strlen(prs->fill);
        _add_to_string(prs->global, prs->g, prs->fill, prs->count);
        prs->g += prs->count;
    }
    if (prs->tmp)
    {
        free(prs->tmp);
        prs->tmp = NULL;
    }
}

void        _copy_inside_dq_(prs *prs)
{
    prs->global[prs->g++] = prs->buffer[prs->i++]; // copy the dq var
    while (prs->buffer[prs->i] != '"' && prs->buffer[prs->i])
    {
        // Loop throw the string inside dq..
        if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
            _dq_copy_dollar_digits_(prs);
        else if (prs->buffer[prs->i] == '\\')
        {
            // This case is one prs->i found the backslash so prs->i need to copy and skip two chars the current one and the next one,
            // This algorithm will help me for skipping the $var if the number of backslashes is odd and looking for $var if the number of bs is even...
            prs->global[prs->g++] = prs->buffer[prs->i++];
            prs->global[prs->g++] = prs->buffer[prs->i++];
            printf("bs == |%c|\n", prs->buffer[prs->i]);
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
            _dq_copy_env_vars_(prs);
        else if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
        {
            printf("? == |%c|\n", prs->buffer[prs->i]);
            prs->count = ft_strlen(ft_itoa(prs->status));
            _add_to_string(prs->global, prs->g, ft_itoa(prs->status), prs->count);
            prs->g += prs->count;
            prs->i += 2;
        }
        else // Copy the  other chars of inside dq "" ...
            prs->global[prs->g++] = prs->buffer[prs->i++];
    }
}

void    _copy_inside_sq_(prs *prs)
{
    prs->global[prs->g++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
        prs->global[prs->g++] = prs->buffer[prs->i++];
}

char *_get_env_var_(char *buffer, prs *prs)
{
    char *global;
    int counter;

    prs->g = 0;
    counter = 0;
    prs->status = 75263;
    // This allocation is just for testing , but in the real project prs->i need to calculate,
    //how much memory prs->i will use first before changing the value of env variables.
    // printf("line counter = [%d]\n", _line_counter_(buffer));
    prs->buffer = buffer;
    counter = _line_counter_(prs);
    printf("length = %d\n", counter);
    prs->global = (char *)malloc(sizeof(char *) * (counter + 1));
    prs->i = -1;
    while (prs->buffer[++prs->i])
    {
        if (prs->buffer[prs->i] == '$' && prs->buffer[prs->i + 1] == '?')
        {
            prs->count = ft_strlen(ft_itoa(prs->status));
            _add_to_string(prs->global, prs->g, ft_itoa(prs->status), prs->count);
            prs->g += prs->count;
            prs->i++;
            printf("out == |%c|\n", buffer[prs->i]);
            continue;

        }
        else if (prs->buffer[prs->i] == '$' && ft_isdigit(prs->buffer[prs->i + 1]))
        {
            _copy_dollar_digits_(prs);
            prs->i--;
            continue;
        }
        else if (prs->buffer[prs->i] == '$' && !(_is_special_(prs->buffer[prs->i + 1])))
        {
            _copy_env_vars_(prs);
            continue;
        }
        else if (prs->buffer[prs->i] == '"')
        {
            puts("im in");
            _copy_inside_dq_(prs);
        }
        else if (prs->buffer[prs->i] == '\'')
            _copy_inside_sq_(prs);
        prs->global[prs->g++] = prs->buffer[prs->i];
    }
    prs->global[prs->g] = '\0';
    return prs->global;
}


int main()
{
    char *line;
    int checker;
    char *tmp;
    size_t bufsize = 1;
    size_t r;
    prs prs;
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
        tmp = _get_env_var_(line, &prs);
        printf("tmp length = |%lu|\n", strlen(tmp));
        printf("tmp after editing = |%s|\n", tmp);
        // _start_parsing(line, prs, &head);
        free(line);
        free(tmp);
        tmp = NULL;
        line = NULL;
        write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    }
    // checker = check_special_(prs->buffer);
    return(0);
}