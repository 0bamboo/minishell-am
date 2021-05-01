/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:08:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/30 16:38:14 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void        add_to_history(char *line, t_mp *prs)
// {
//     printf("Im in History :\n");
// }


void _free_(t_mp *prs)
{
    if (prs->global)
        free(prs->global);
    if (prs->cmds)
    {
        int i = -1;
        while (prs->cmds[++i])
            free(prs->cmds[i]);
        free(prs->cmds);    
    }
    if (prs->temp)
        free(prs->temp);
    if (prs->sp)
        free(prs->sp);
    if (prs)
        free(prs);
}
void  minishell(t_mp *prs)
{
    char *line;
    // t_cmd_list *head;
    
    line = NULL;
    // int i;
    // head = malloc(sizeof(p_list));
    write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    while(get_next_line(0, &line) > 0)
    {
    // prs->sp = malloc(sizeof(t_sp));
        // add_to_history(line, prs);
        // head = malloc(sizeof(p_list));
        // head = NULL;
        if (line)
        {
            line[ft_strlen(line) - 1] = '\0';
        }
        if (!ft_strcmp(line, "exit"))
        {
            // free(line);
            // _free_(prs);
            // line = NULL;
            // free(prs->sp);
            // free(prs);
            exit(0);
        }
        _start_parsing(line, prs);
        // _free_(prs);
        
        // free(line);
        // line = NULL;
        write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    }
}

void        _initialize_vars(t_mp *prs)
{
    prs->cmds = NULL;
    prs->er = 0;
    prs->i = 0;
    prs->buff = NULL;
    prs->env = NULL;
    prs->temp = NULL;
    prs->global = NULL;
    
    
}

int main()
{
    // You need to allocate all the structs that you will use in this program, 
    // for handling some mermory errors......
    t_mp *prs;
    // t_sp sp;

    // prs.sp = &sp;
    prs = malloc(sizeof(t_mp));
    prs->sp = malloc(sizeof(t_sp));
    _initialize_vars(prs);
    minishell(prs);
    // free(prs);
    return 0;
}