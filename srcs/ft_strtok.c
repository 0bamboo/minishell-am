/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdait-m <abdait-m@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:10:55 by abdait-m          #+#    #+#             */
/*   Updated: 2021/03/14 22:10:55 by abdait-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char        *my_strtok(char *s, char *check)
{
    int j;
    int i;
    static char *input;
    char *result;


    if (s != NULL)
        input = s;
    if (input == NULL)
        return NULL;
    result = malloc(sizeof(char) * (strlen(input) + 1));
    i = 0;
    while (input[i])
    {
        j = -1;
        while (check[++j])
        {
            if (input[i] != check[j])
                result[i] = input[i];
            else
            {
                result[i] = '\0';
                input = input + i + 1;
                return result;
            }
        }
        i++;
    }
    result[i] = '\0';
    input = NULL;
    return result;
}