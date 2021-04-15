/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:08:05 by abdait-m          #+#    #+#             */
/*   Updated: 2021/04/14 23:04:59 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void        add_to_history(char *line, ms_p *prs)
// {
//     printf("Im in History :\n");
// }

void  minishell(ms_p *prs)
{
    char *line;
    t_cmd_list *head;
    
    line = NULL;
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
    ms_p prs;
    // s_split sp;

    // prs.sp = &sp;
    minishell(&prs);
    return 0;
}