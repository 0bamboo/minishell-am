/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/20 15:28:36 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"




int     _check_for_special_chars_(char *buff)
{
    int i;

    i = 0;
    while (buff[i])
    {
        if (buff[i] == '"')
            while (buff[++i] && buff[i] != '"');
        else if (buff[i] == '\'')
            while (buff[++i] && buff[i] != '\'');
        if (_char_in_tab_(buff[i], "><|"))
            return 1;
        i++;
    }
    return 0;
}


// void _push_back_normal_tokens_(t_cmd_list **head, t_mp *prs)
// {
//     t_cmd_list *curr;
//     t_cmd_list *new;
    
//     //  use double pointer for declaring the struct ...
//     // prs->err.i = 0;
//     new = malloc(sizeof(t_cmd_list));
//     new->prev = NULL;
//     new->next = NULL;
//     new->beg = 1;
//     new->end = 1;
//     if (!(*head))
//         (*head) = new;
//     else
//     {
//         curr = (*head);
//         while (curr->next)
//             curr =  curr->next;
//         curr->next = new;
//         new->prev = curr;
//     }
// }

int _count_token_length_(t_mp *prs, int index)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while (prs->cmds[index][++i])
    {
        if (prs->cmds[index][i] == ' ')
            continue;
        else if (prs->cmds[index][i] == '>' || prs->cmds[index][i] == '<')
        {
            count++;
            if ( prs->cmds[index][i + 1] ==  '>')
                i++;
        }
        else
        {
            count++;
            while (prs->cmds[index][i] && prs->cmds[index][i] != ' ' && prs->cmds[index][i] != '>' && prs->cmds[index][i] != '<')
            {
                if (prs->cmds[index][i] == '"')
                {
                    i++;
                    while (prs->cmds[index][i] && prs->cmds[index][i] != '"')
                    {
                        if (prs->cmds[index][i] == '\\')
                        {
                            i += 2;
                            continue;
                        }
                        i++;
                    }
                }
                else if (prs->cmds[index][i] == '\'')
                {
                    i++;
                    while (prs->cmds[index][i] && prs->cmds[index][i] != '\'')
                        i++;
                }
                i++;
            }
            i--;
        }
 
    }
    return (count);
}

int     _size_of_arg_(char *buffer, int i)
{
    // int i;
    int counter;

    // i = 0;
    counter = 0;
    while (buffer[i] && buffer[i] == ' ')
        i++;
    while (buffer[i])
    {
        if (buffer[i] == '"')
        {
            i++;
            counter++;
            while (buffer[i] && buffer[i] != '"')
            {
                if (buffer[i] == '\\')
                {
                    counter += 2;
                    i += 2;
                    continue;
                }
                i++;
                counter++;
            }
        }
        else if (buffer[i] == '\'')
        {
            counter++;
            i++;
            while (buffer[i] && buffer[i] != '\'')
            {
                counter++;
                i++;
            }
        }
        if (buffer[i] == ' ' || buffer[i] == '>' || buffer[i] == '<')
            break;
        i++;
        counter++;
    }
    return (counter);
}

void _free_tab_(char **buffer)
{
    int     i;
    
    i = -1;
    if (buffer)
    {
        puts("im in ");
        if (buffer[++i])
            while (buffer[i])
                free(buffer[i++]);
        free(buffer);
        buffer = NULL; 
    }
}

void _fill_list_for_normal_args_(t_mp *prs, char **args, char **files, int len)
{
    t_cmd_list *curr;
    int     i;
    int     j;
    
    prs->head = malloc(sizeof(t_cmd_list));
    curr = prs->head;
    curr->nbrpipe = 0;
    curr->next = NULL;
    if (args[0])
        curr->command = ft_strdup(args[0]);
    curr->args = malloc(sizeof(char *) * (len + 1));
    i = -1;
    puts("im here");
    while (args[++i])
        curr->args[i] = ft_strdup(args[i]);
    j = -1;
    while (files[++j])
        curr->args[i++] = ft_strdup(files[j]);
    curr->args[i] = NULL;
    i = -1;
    while (curr->args[++i])
        printf("=|%s|= ", curr->args[i]);
    puts("");
    if (i == len)
        puts("YAAAAY");
    puts(curr->command);
}


void        _fix_the_order_(t_mp *prs, char **buffer, int len)
{
    char **args;
    char **files;
    int i;
    int file;
    int arg;

    args = malloc(sizeof(char *) * (len + 1));
    files = malloc(sizeof(char *) * (len + 1));
    file = 0;
    arg = 0;
    i = 0;
    prs->er = 0;
    while (buffer[i])
    {
        if (buffer[i][0] == '>' || buffer[i][0] == '<')
        {
            if (buffer[i][1] == '>')
            {
                files[file++] = ft_strdup(">>");
                files[file++] = ft_strdup(buffer[++i]);
                i++;
            }
            else if (buffer[i][0] == '<')
            {
                files[file++] = ft_strdup("<");
                files[file++] = ft_strdup(buffer[++i]);
                i++;
            }
            else
            {
                files[file++] = ft_strdup(">");
                files[file++] = ft_strdup(buffer[++i]);
                i++;
            }
        }
        else
            args[arg++] = ft_strdup(buffer[i++]);
    }
    args[arg] = NULL;
    files[file] = NULL;
    file = -1;
    printf("++%s++\n", args[0]);
    while (files[++file])
        printf("file______|%s|_____\n", files[file]);
    file = -1;
    while (args[++file])
        printf("args______|%s|_____\n", args[file]);
    // if (i == len)
    //     puts("YAAAAY");
    _fill_list_for_normal_args_(prs, args, files, len);
    _free_tab_(args);
    _free_tab_(files);
}

void _handle_normal_args_(t_mp *prs, int index)
{
    int     i;
    int     len;
    char    **tmp;
    char *buffer;
    int size;
    // echo "ls"hello> file >hello

    i = 0;
    // prs->head = malloc(sizeof(t_cmd_list));
    len = _count_token_length_(prs, index);
    printf("t =========== %d\n", len);
    size = 0;
    buffer = prs->cmds[index];
    tmp = malloc(sizeof(char *) * (len + 1));
    while (buffer[i] && size < len)
    {
        if (buffer[i] == '>' || buffer[i] == '<')
        {
            if (buffer[i + 1] == '>')
            {
                tmp[size++] = ft_strdup(">>");
                i += 2;
            }
            else if (buffer[i] == '<')
            {
                tmp[size++] = ft_strdup("<");
                i++;
            }
            else
            {
                tmp[size++] = ft_strdup(">");
                i++;
            } 
        }
        else if (buffer[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            int l = _size_of_arg_(buffer, i);
            printf("length ==== {%d}\n", l);
            tmp[size] = malloc(sizeof(char) * (l + 1));
            int j = 0;
            while (buffer[i])
            {
                if (buffer[i] == '>' || buffer[i] == '<' || buffer[i] == ' ')
                    break;
                else if (buffer[i] == '"')
                {
                    tmp[size][j++] = buffer[i++];
                    while (buffer[i] && buffer[i] != '"')
                    {
                        if (buffer[i] == '\\')
                        {
                            tmp[size][j++] = buffer[i++];
                            tmp[size][j++] = buffer[i++];
                            continue;
                        }
                        tmp[size][j++] = buffer[i++];
                    }
                    tmp[size][j++] = buffer[i++];
                }
                else if (buffer[i] == '\'')
                {
                    tmp[size][j++] = buffer[i++];
                    while (buffer[i] && buffer[i] != '\'')
                        tmp[size][j++] = buffer[i++];
                    tmp[size][j++] = buffer[i++];
                }
                else
                    tmp[size][j++] = buffer[i++];
            }
            tmp[size++][j] = '\0';
        }
    }
    tmp[size] = NULL;
    i = -1;
    while (tmp[++i])
        printf("{=====|%s|=====}\n", tmp[i]);
    _fix_the_order_(prs, tmp, len);
    _free_tab_(tmp);
}


// void        _copy_tokens_data_(t_mp *prs, int index)
// {
//     // t_cmd_list *curr;

//     // curr = prs->head;
//     if (_if_pipe_(prs->cmds[index]))
//     {
//         // handle pipe ....
//     }
//     else
//     {
//         _handle_normal_args_(prs, index);
//     }
    
// }
   




// int     _if_pipe_(char *check)
// {
//     int i;

//     i = -1;
//     while (check[++i])
//     {
//         if (check[i] == '"')
//         {
//             i++;
//             while (check[i] && check[i] != '"')
//             {
//                 if (check[i] == '\\')
//                 {
//                     i += 2;
//                     continue;
//                 }
//                 i++;
//             }
//         }
//         else if (check[i] == '\'')
//         {
//             i++;
//             while (check[i] && check[i] != '\'')
//                 i++;
//         }
//         else if (check[i] == '|')
//             return 1;
//     }
//     return 0;
// }




void _start_parsing(char *line, t_mp *prs)
{
    // t_sp *sp;
    int i;
    // prs->head = malloc(sizeof(t_cmd_list));
	// char *tmp;
    
	line = ft_strtrim(line, " \t\v\n\r");
    if (_handle_syntax_errors(line, prs))
        _raise_an_exception();
    else
    {
		_split_tokens(prs, prs->sp, line, ';');
        i = -1;
        // echo $$0$?"hi agina \\\$0 $$9abdennacer \\$?$?$??? hi \" \\\" out"
        while (prs->cmds[++i])
        {
            prs->cmds[i] = _get_env_vars_(prs->cmds[i], prs);
            _handle_normal_args_(prs, i);
            // if (_if_pipe_(prs->cmds[i]))
            //     puts("PIPE IN");
            // _copy_tokens_data_(prs, i);
            // prs->cmds[i] = _handle_backslash_(prs, prs->cmds[i]);
            // free(prs->global);
            // printf(" im out {/global}   ---> : |%s|\n", prs->cmds[i]);
            // if (prs->cmds[i])
            //     _copy_tokens_data_(prs->cmds[i], prs, head);
        }
        i = -1;
        while (prs->cmds[++i])
            printf("---> |%s|\n", prs->cmds[i]);
    }
	// free(tmp);
}