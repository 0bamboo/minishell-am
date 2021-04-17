/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:08:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/17 16:19:20 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void        add_to_history(char *line, t_mp *prs)
// {
//     printf("Im in History :\n");
// }

void  minishell(t_mp *prs)
{
    char *line;
    t_cmd_list *head;
    
    line = NULL;
    int i;
    prs->sp = malloc(sizeof(t_sp));
    // head = malloc(sizeof(p_list));
    write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    while(get_next_line(0, &line) > 0)
    {
        // add_to_history(line, prs);
        // head = malloc(sizeof(p_list));
        head = NULL;
        if (!ft_strcmp(line, "exit"))
        {
            free(line);
            line = NULL;
            i = -1;
            if (prs)
            {
                // while (prs->cmds[++i])
                //     free(prs->cmds[i]);
                // free(prs->cmds);
                // free(prs->sp->tmp);
                i = -1;
                // while (prs->global[++i])
                //     free(prs->global[i]);
                // free(prs->global);
                // free(prs->buff);
                // free(prs->fill);
                // // i = -1;
                // // while (prs->cmds[++i])
                // //     free(prs->cmds[i]);
                // free(prs->sp);
                // free(prs);
            }
            exit(0);
        }
        _start_parsing(line, prs, &head);
        
        free(line);
        line = NULL;
        write(1, "\033[0;35m mini$hell~~> \033[0;37m", 28);
    }
}


int main()
{
    // You need to allocate all the structs that you will use in this program, 
    // for handling some mermory errors......
    t_mp *prs;
    // t_sp sp;

    // prs.sp = &sp;
    prs = malloc(sizeof(t_mp));
    minishell(prs);
    // free(prs);
    return 0;
}