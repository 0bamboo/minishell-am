/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/21 15:38:29 by abdait-m         ###   ########.fr       */
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

int _count_token_length_(t_mp *prs)
{
    int i;
    int count;

    i = -1;
    count = 0;
    while (prs->buffer[++i])
    {
        if (prs->buffer[i] == ' ')
            continue;
        else if (prs->buffer[i] == '>' || prs->buffer[i] == '<')
        {
            count++;
            if ( prs->buffer[i + 1] ==  '>')
                i++;
        }
        else
        {
            count++;
            while (prs->buffer[i] && prs->buffer[i] != ' ' && prs->buffer[i] != '>' && prs->buffer[i] != '<')
            {
                if (prs->buffer[i] == '"')
                {
                    i++;
                    while (prs->buffer[i] && prs->buffer[i] != '"')
                    {
                        if (prs->buffer[i] == '\\')
                        {
                            i += 2;
                            continue;
                        }
                        i++;
                    }
                }
                else if (prs->buffer[i] == '\'')
                {
                    i++;
                    while (prs->buffer[i] && prs->buffer[i] != '\'')
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
        if (buffer[++i])
            while (buffer[i])
                free(buffer[i++]);
        free(buffer);
        buffer = NULL; 
    }
}

void _fill_list_for_normal_args_(t_mp *prs, char **args, char **files)
{
    t_cmd_list *curr;
    int     i;
    int     j;
    
    // prs->head = malloc(sizeof(t_cmd_list));
    curr = prs->head;
    curr->nbrpipe = 0;
    curr->next = NULL;
    if (args[0])
        curr->command = ft_strdup(args[0]);
    curr->args = malloc(sizeof(char *) * (prs->len + 1));
    i = -1;
    // puts("im here");
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
    if (i == prs->len)
        puts("YAAAAY");
    // puts(curr->command);
}

void _copy_files_(t_mp *prs)
{
    if (prs->array[prs->i][1] == '>')
    {
        prs->files[prs->j++] = ft_strdup(">>");
        prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
        prs->i++;
    }
    else if (prs->array[prs->i][0] == '<')
    {
        prs->files[prs->j++] = ft_strdup("<");
        prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
        prs->i++;
    }
    else
    {
        prs->files[prs->j++] = ft_strdup(">");
        prs->files[prs->j++] = ft_strdup(prs->array[++prs->i]);
        prs->i++;
    }
}

void        _fix_the_order_(t_mp *prs)
{
    int arg;

    prs->j = 0;
    arg = 0;
    prs->i = 0;
    prs->args = malloc(sizeof(char *) * (prs->len + 1));
    prs->files = malloc(sizeof(char *) * (prs->len + 1));
    while (prs->array[prs->i])
    {
        if (prs->array[prs->i][0] == '>' || prs->array[prs->i][0] == '<')
        {
            _copy_files_(prs);
            // if (prs->array[prs->i][1] == '>')
            // {
            //     prs->files[file++] = ft_strdup(">>");
            //     prs->files[file++] = ft_strdup(prs->array[++prs->i]);
            //     prs->i++;
            // }
            // else if (prs->array[prs->i][0] == '<')
            // {
            //     prs->files[file++] = ft_strdup("<");
            //     prs->files[file++] = ft_strdup(prs->array[++prs->i]);
            //     prs->i++;
            // }
            // else
            // {
            //     prs->files[file++] = ft_strdup(">");
            //     prs->files[file++] = ft_strdup(prs->array[++prs->i]);
            //     prs->i++;
            // }
        }
        else
            prs->args[arg++] = ft_strdup(prs->array[prs->i++]);
    }
    prs->args[arg] = NULL;
    prs->files[prs->j] = NULL;
    // file = -1;
    // printf("++%s++\n", prs->args[0]);
    // while (prs->files[++file])
    //     printf("file______|%s|_____\n", prs->files[file]);
    // file = -1;
    // while (prs->args[++file])
    //     printf("args______|%s|_____\n", prs->args[file]);
    // if (prs->i == prs->len)
    //     puts("YAAAAY");
    // _fill_list_for_normal_args_(prs, prs->args, prs->files, prs->len);
    // _free_tab_(prs->args);
    // _free_tab_(prs->files);
}

void    _copy_redirs_(t_mp *prs)
{
    if (prs->buffer[prs->i + 1] == '>')
    {
        prs->array[prs->size++] = ft_strdup(">>");
        prs->i += 2;
    }
    else if (prs->buffer[prs->i] == '<')
    {
        prs->array[prs->size++] = ft_strdup("<");
        prs->i++;
    }
    else
    {
        prs->array[prs->size++] = ft_strdup(">");
        prs->i++;
    }
}

void _copy_args_with_dq_(t_mp *prs)
{
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '"')
    {
        if (prs->buffer[prs->i] == '\\')
        {
            prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
            prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
            continue;
        }
        prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    }
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
}

void _copy_args_with_sq_(t_mp *prs)
{
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
        prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
}

void _handle_normal_args_(t_mp *prs, char *tmp)
{
    int     len;
    // echo "ls"hello> file >hello

    prs->i = 0;
    // prs->head = malloc(sizeof(t_cmd_list));
    prs->buffer = tmp;
    len = _count_token_length_(prs);
    printf("t =========== %d\n", len);
    prs->size = 0;
    printf("cmds = |%s|\n", prs->buffer);
    prs->array = malloc(sizeof(char *) * (len + 1));
    while (prs->buffer[prs->i] && prs->size < len)
    {
        if (prs->buffer[prs->i] == '>' || prs->buffer[prs->i] == '<')
        {
            _copy_redirs_(prs);
            // if (prs->buffer[prs->i + 1] == '>')
            // {
            //     prs->array[prs->size++] = ft_strdup(">>");
            //     prs->i += 2;
            // }
            // else if (prs->buffer[prs->i] == '<')
            // {
            //     prs->array[prs->size++] = ft_strdup("<");
            //     prs->i++;
            // }
            // else
            // {
            //     prs->array[prs->size++] = ft_strdup(">");
            //     prs->i++;
            // } 
        }
        else if (prs->buffer[prs->i] == ' ')
        {
            prs->i++;
            continue;
        }
        else
        {
            int l = _size_of_arg_(prs->buffer, prs->i);
            printf("length ==== {%d}\n", l);
            prs->array[prs->size] = malloc(sizeof(char) * (l + 1));
            prs->j = 0;
            //echo >file "hiag"'hi'hi >file "hi"
            while (prs->buffer[prs->i])
            {
                puts("im in==");
                if (prs->buffer[prs->i] == '>' || prs->buffer[prs->i] == '<' || prs->buffer[prs->i] == ' ')
                    break;
                else if (prs->buffer[prs->i] == '"')
                {
                    _copy_args_with_dq_(prs);
                    // prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                    // while (prs->buffer[prs->i] && prs->buffer[prs->i] != '"')
                    // {
                    //     if (prs->buffer[prs->i] == '\\')
                    //     {
                    //         prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                    //         prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                    //         continue;
                    //     }
                    //     prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                    // }
                    // prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                }
                else if (prs->buffer[prs->i] == '\'')
                {
                    _copy_args_with_sq_(prs);
                    // prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                    // while (prs->buffer[prs->i] && prs->buffer[prs->i] != '\'')
                    //     prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                    // prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
                }
                else
                    prs->array[prs->size][prs->j++] = prs->buffer[prs->i++];
            }
            puts("im out");
            prs->array[prs->size++][prs->j] = '\0';
        }
    }
    prs->array[prs->size] = NULL;
    prs->i = -1;
    // while (prs->array[++i])
    //     printf("{=====|%s|=====}\n", prs->array[i]);
    prs->len = len;
    _fix_the_order_(prs);
    _free_tab_(prs->array);
}


   




int     _if_pipe_(t_mp *prs, int index)
{
    int i;
    // int count;

    i = -1;
    prs->nbrpipe = 0;
    while (prs->cmds[index][++i])
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
            // i++;
            while (prs->cmds[index][++i] && prs->cmds[index][i] != '\'');
                // i++;
        }
        else if (prs->cmds[index][i] == '|')
            prs->nbrpipe++;
    }
    if (prs->nbrpipe)
        return (1);
    return (0);
}

void _fill_first_node_(t_mp *prs, char **args, char **files)
{
    t_cmd_list *new;
    
    new = malloc(sizeof(t_cmd_list));
    puts("im in ");
    // new = prs->head;
    puts("first node");
    printf("===|%d|\n", prs->nbrpipe);
    int i =-1;
    while (args[++i])
        printf("|%s| ", args[i]);
    i =-1;
    while (files[++i])
        printf("|%s| ", files[i]);
    // new->nbrpipe = prs->nbrpipe;
    puts("first node");
    // if (args[0])
    //     new->command = ft_strdup(args[0]);
    printf("len inside pipe list : |%d|\n", prs->len);
    new->args = malloc(sizeof(char *) * (prs->len + 1));
    puts("hi agian");
    i = -1;
    int j = -1;
    while (args[++i])
        new->args[i] = ft_strdup(args[i]);
    puts("hi agian");
    while (files[++j])
        new->args[i++] = ft_strdup(files[j]);
    new->next = NULL;
    new = prs->head;
    
    
}

void _push_back_(t_mp *prs, char **args, char **files)
{
    t_cmd_list *new;
    t_cmd_list *curr;

    new = malloc(sizeof(t_cmd_list));
    new->next = NULL;
    curr = prs->head;
    new->nbrpipe = prs->nbrpipe;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
    int i = -1;
    int j = -1;
    if (args[0])
        new->command = args[0];
    while (args[++i])
        new->args[i] = args[i];
    while (files[++j])
        new->args[i++] = files[j];
    puts("PUSHED");
}

void    _fill_list_for_pipe_args_(t_mp *prs, char **args, char **files)
{
    // t_cmd_list *curr;
    
    // curr = prs->head;
    puts("inside fill ------------------------");
    if (prs->head == NULL)
    {
        puts("hello");
        _fill_first_node_(prs, args, files);
        puts("inside fill ------------------------");

    }
    else
    {
        puts("hello2");
        _push_back_(prs, args, files);
        puts("inside fill ------------------------");
    }
    
}

void        _handle_pipe_args_(t_mp *prs)
{
    int     i;

    i = -1;
    while (prs->pipe[++i])
    {
        _handle_normal_args_(prs, prs->pipe[i]);
        int j =  -1;
        printf("pipe args ==>  ");
        while (prs->args[++j])
            printf("|%s| ", prs->args[j]);
        j = -1;
        puts("files : ");
        while (prs->files[++j])
            printf("|%s| ", prs->files[j]);
        puts("");
        puts("1============hahah");
        _fill_list_for_pipe_args_(prs, prs->args, prs->files);
        puts("2============hahah");
        _free_tab_(prs->args);
        _free_tab_(prs->files);
    }
    i = -1;
    while (prs->head)
    {
        printf("---pipe list----> |%d| |%s|", prs->head->nbrpipe, prs->head->command);
        while (prs->head->args[++i])
            printf("---------> pipe args = |%s|\n", prs->head->args[i]);
        prs->head = prs->head->next;
    }
}

void        _copy_tokens_data_(t_mp *prs, int index)
{
    // t_cmd_list *curr;

    // curr = prs->head;
    prs->head = malloc(sizeof(t_cmd_list));
    prs->head = NULL;
    if (_if_pipe_(prs, index))
    {
        prs->pipe = _split_tokens(prs->sp, prs->cmds[index], '|');
        int i;
        i = -1;
        while (prs->pipe[++i])
            printf("pipe = |%s| len =  |%lu|\n", prs->pipe[i], ft_strlen(prs->pipe[i]));
        _handle_pipe_args_(prs);
        puts("pipe");
        // handle pipe ....
    }
    else
    {
        _handle_normal_args_(prs, prs->cmds[index]);
        _fill_list_for_normal_args_(prs, prs->args, prs->files);
        _free_tab_(prs->args);
        _free_tab_(prs->files);
        
    }
}



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
		prs->cmds = _split_tokens(prs->sp, line, ';');
        i = -1;
        // echo $$0$?"hi agina \\\$0 $$9abdennacer \\$?$?$??? hi \" \\\" out"
        while (prs->cmds[++i])
        {
            prs->cmds[i] = _get_env_vars_(prs->cmds[i], prs);
            _copy_tokens_data_(prs, i);
            // _handle_normal_args_(prs, i);
            // prs->er = _if_pipe_(prs, prs->cmds[i]);
            printf("pipe counter == |%d|\n", prs->nbrpipe);
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