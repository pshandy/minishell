/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_replace(char *str, char *old, char *new)
{
	int		i;
	int		words;
	char	*result;

	if (old == NULL || new == NULL)
		return (NULL);

    int newWlen = ft_strlen(new);
    int oldWlen = ft_strlen(old);

	i = 0;
	words = 0;
	while (str[i])
	{
		if (ft_strstr(&str[i], old) == &str[i])
		{
			words++;
			i += oldWlen - 1;
		}
		i++;
	}

	result = (char*)malloc(i + words * (newWlen - oldWlen) + 1);

    i = 0;
    while (*str) {

        if (ft_strstr(str, old) == str) {
            ft_strcpy(&result[i], new);
            i += newWlen;
            str += oldWlen;
        }
        else
            result[i++] = *str++;
    }

    result[i] = '\0';
	return (result);
}
