/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/17 16:15:39 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"




void        _initialize_vars(t_sp *ps)
{
    ps->i = 0;
    
}


void        _free_tokens_data_(t_cmd_list **head)
{
    int i;

    i = -1;
    if ((*head)->args)
    {
        while ((*head)->args[++i])
            free((*head)->args[i]);
        free((*head)->args);   
    }
    if ((*head)->command)
        free((*head)->command);
}


void        _free_all_tokens(t_cmd_list **head)
{
    t_cmd_list *next;
    
    if ((*head))
    {
        while (*head)
        {
            next = (*head)->next;
            _free_tokens_data_(head);
            free((*head));
            (*head) = next;
        }
        (*head) = NULL;
    }
}


void    _free_all_(t_mp *prs, t_cmd_list **head)
{
    _free_all_tokens(head);
    prs->err.i = 0;
}

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


void _push_back_normal_tokens_(t_cmd_list **head, t_mp *prs)
{
    t_cmd_list *curr;
    t_cmd_list *new;
    
    //  use double pointer for declaring the struct ...
    prs->err.i = 0;
    new = malloc(sizeof(t_cmd_list));
    new->prev = NULL;
    new->next = NULL;
    new->beg = 1;
    new->end = 1;
    if (!(*head))
        (*head) = new;
    else
    {
        curr = (*head);
        while (curr->next)
            curr =  curr->next;
        curr->next = new;
        new->prev = curr;
    }
}



// void        _copy_tokens_data_(char *token, t_mp *prs, t_cmd_list **head)
// {
//     char **tmp;
//     int i;
//     t_sp sp;

//     i = 0;
//     prs->sp = &sp;
//     // prs->count = 0;
//     // prs->sp = malloc(sizeof(t_sp));
//     // tmp = NULL;
//     *head = NULL;
//     // puts("im in copy");
//     // if (!_check_for_special_chars_(token))
//     tmp = _split_tokens(prs->sp, token, ' '); // _push_back_normal_tokens_(head, prs);  
//     // else
//     //     puts("special tokens");
//     // puts("w hi");
//     // printf("tmp[%d]=%s", 1,tmp[1]);
//     while (tmp[i])
//     {
//         // printf("pushing  = |%s|\n", tmp[i]);
//         i++;
//     }
//     // free(token);
//     // token = NULL;
//     // i = 0;
//     // while (tmp[i])     
//     //     free(tmp[i]);
//     // free(tmp);
// }



int     in(char *check, char c)
{
    while (*check)
    {
        if (*check == c)
            return 1;
        check++;
    }
    return 0;
}




void _start_parsing(char *line, t_mp *prs, t_cmd_list **head)
{
    // t_sp *sp;
    int i;
	char *tmp;
    
    *head = NULL;
    // sp = malloc(sizeof(t_sp));
    _initialize_vars(prs->sp);
	tmp = ft_strtrim(line, " \t\v\n\r");
    if (_handle_syntax_errors(tmp, prs))
        _raise_an_exception();
    else
    {
		_split_tokens(prs, prs->sp, line, ';');
        i = -1;
        // printf("size = |%d|\n", prs->sp->size);
        while (prs->cmds[++i])
        {
            prs->cmds[i] = _get_env_vars_(prs->cmds[i], prs);
            // if (in(prs->cmds[i], '"'))
            prs->cmds[i] = _handle_backslash_(prs, prs->cmds[i]);
            printf(" im out {global}   ---> : |%s|\n", prs->cmds[i]);
            // if (prs->cmds[i])
            //     _copy_tokens_data_(prs->cmds[i], prs, head);
        }
        i = -1;
		if (prs)
		{
			if (prs->cmds)
			{
				while (prs->cmds[++i])
					free(prs->cmds[i]);
			}
			free(prs->cmds);
			// free(prs->sp->tmp);
		// 	i = -1;
		// 	while (prs->cmds[++i])
		// 		free(prs->cmds[i]);
		// 	free(prs->cmds);
		// 	// free(prs->sp);
		}
    }
	free(tmp);
    // free(prs->sp);
}