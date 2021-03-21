/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:38:31 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/21 23:18:09 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int _check_parsing_errors(char *line)
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
        if (line[i] == ';' && line[i + 1] == ';' && open_dq == 0 && open_sq == 0)
            return 1;
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
    if (_check_parsing_errors(line))
        raise_an_exception();
    else 
    {
        prs->sc_cmds = _split_tokens(&sp, line, ';');
        i = 0;
        prs->space_cmd = (char ***)malloc(sizeof(char **) * (sp.size));
        while (prs->sc_cmds[i])
        {
            prs->space_cmd[i] = _split_tokens(&sp, prs->sc_cmds[i], ' ');
            i++;
        }
        i = -1;
        while (prs->sc_cmds[++i])
        {
            j = -1;
            while (prs->space_cmd[i][++j])
                printf("----|%s|----\t", prs->space_cmd[i][j]);
            printf("\n");
        }
        write(1, "free time\n", 10);
        // while (prs->space_cmd[i] != NULL)
        // {
        //     j = 0;
        //     while (prs->space_cmd[i][j] != NULL)
        //     {
        //         free(prs->space_cmd[i][j]);
        //         prs->space_cmd[i][j] = NULL;
        //         j++;
        //     }
        //     free(prs->space_cmd);
        //     prs->space_cmd[i] = NULL;
        // }
        // printf("size of triple pointer : |%d|\n", i);
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