/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/20 00:09:51 by abdait-m         ###   ########.fr       */
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


void _fill_list_data_(t_mp *prs, int index)
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
            tmp[size] = malloc(sizeof(char) * (_size_of_arg_(buffer, i)));
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
        printf("=====|%s|=====\n", tmp[i]);
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
//         _fill_list_data_(prs, index);
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
            _fill_list_data_(prs, i);
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