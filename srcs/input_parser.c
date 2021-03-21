/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/21 12:56:48 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  Try to make a function that calculates the number of parenthesis and check if it is an error or not,
// use open close method  : if " is open  then the next one should close it etcetera.....


int count_parenthesis(char *line)
{
    int open_sq;
    int count_sq;
    int open_dq;
    int count_dq;
    int i;

    i = -1;
    open_sq = 0;
    open_dq = 0;
    count_sq = 0;
    count_dq = 0;
    while (line[++i])
    {
        if (line[i] == '"' && open_dq == 0 && open_sq == 0)
        {
            count_dq++;
            open_dq = 1;
        }
        else if (line[i] == '"' && open_dq == 1)
        {
            count_dq--;
            open_dq = 0;
        }
        if (line[i] == '\'' && open_sq == 0 && open_dq == 0)
        {
            count_sq++;
            open_sq = 1;
        }
        else if (line[i] == '\'' && open_sq == 1)
        {
            count_sq--;
            open_sq = 0;
        }
    }
    return (count_sq + count_dq);
}


// Try to use this split for your parsing :

// typedef struct 
// {
//     char **p;
//     int size;
//     int i;
//     int j;
//     int check_pp;
//     int check_p;
// } s_split;

// static int			ft_count_words(char const *s, char c, s_split *sp)
// {
// 	int	count;

// 	count = 0;
// 	while (*s && *s == c)
// 		s++;
// 	while (*s)
// 	{
//         if ('"' == *s && sp->check_p % 2 == 0)
//             sp->check_pp += 1;
//         if ('\'' == *s && sp->check_pp % 2 == 0)
//             sp->check_p += 1;
// 		if ((((*s == c && *(s + 1) != c) || *(s + 1) == '\0')) && sp->check_p % 2 == 0 && sp->check_pp % 2 == 0)
// 			count++;
// 		s++;
// 	}
//     printf("how many words : %d\n", count);
// 	return (count);
// }

// static int			ft_len_words(char const *s, char c)
// {
// 	int	k;

// 	k = 0;
// 	while (s[k] && s[k] != c)
// 		k++;
// 	return (k);
// }

// static char			**ft_free(char **ptr, int size)
// {
// 	int i;

// 	i = 0;
// 	while (i++ < size)
// 		free(ptr[i]);
// 	free(ptr);
// 	ptr = NULL;
// 	return (NULL);
// }

// char				**_split_tokens(s_split *sp, char const *s, char c)
// {
// 	if (!s)
// 		return (NULL);
//     sp->check_pp = 0;
//     sp->check_p = 0;
// 	sp->size = ft_count_words(s, c, sp);
// 	if (!(sp->p = (char **)malloc(sizeof(char*) * (sp->size + 1))))
// 		return (NULL);
// 	sp->i = 0;
//     sp->check_pp = 0;
//     sp->check_p = 0;
// 	while (sp->i < sp->size)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		if (!(sp->p[sp->i] = (char *)malloc(sizeof(char) * (ft_len_words(s, c) + 1))))
// 			return (ft_free(sp->p, sp->size));
// 		sp->j = 0;
// 		while (*s)
//         {
//             if (*s == '\'' && sp->check_pp % 2 == 0)
//                 sp->check_p += 1;
//             if (*s == '"' && sp->check_p % 2 == 0)
//                 sp->check_pp += 1;
//             sp->p[sp->i][sp->j++] = *s++;
//             if (*s == c && sp->check_pp % 2 == 0 && sp->check_p % 2 == 0)
//                 break;
//         }
// 		sp->p[sp->i++][sp->j] = '\0';
// 	}
// 	sp->p[sp->i] = NULL;
// 	return (sp->p);
// }

void        raise_an_exception()
{
    printf("Parsing Error !!\n");
}

void        initialize_vars(s_split *ps)
{
    ps->check_dq = 0;
    ps->check_sq = 0;
    ps->i = 0;
    
}

// void _free_triple_pointer(sc_parse *prs)
// {
//     int i; 
// }


void start_parsing(char *line, sc_parse *prs)
{
    s_split sp;
    int j;
    int i;
    
    initialize_vars(&sp);
    if (count_parenthesis(line))
        raise_an_exception();
    else 
    {
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        i = 0;
        // printf("this the first string ---> |%s|\n", prs->sc_cmds[i]);
        prs->space_cmd = (char ***)malloc(sizeof(char **) * (sp.size));
        while (prs->sc_cmds[i])
        {
            // Fix this one how to fill the table of commands and its options and arguments
            prs->space_cmd[i] = _split_tokens(&sp, prs->sc_cmds[i], ' ');
            printf("|%s|--> |%s|\n", prs->sc_cmds[i], prs->space_cmd[i][0]);
            i++;
        }
        i = 0;
        printf("--command--        --option--         -- args -->\n");
        while (prs->space_cmd[i])
        {
            j = -1;
            while (prs->space_cmd[i][++j])
                printf("----|%s|----\t", prs->space_cmd[i][j]);
            printf("\n");
            i++;
            write(1, "\n\nim here\n\n", 11);
        }
        while (prs->space_cmd[i])
        {
            j = -1;
            while (prs->space_cmd[i][++j])
            {
                free(prs->space_cmd[i][j]);
                prs->space_cmd[i][j] = NULL;
            }
            free(prs->space_cmd);
            prs->space_cmd[i] = NULL;
        }
        printf("size of triple pointer : |%d|\n", i);
        // i = 0;
        // while (prs->space_cmd[i])
        // {
        //     j = 0;
        //     while (prs->space_cmd[i][j])
        //     {
        //         printf("---%s---\n", prs->space_cmd[i][j]);
        //         j++;
        //     }
        //     i++;
        // }
    }
}