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

static int	get_words(char *str, char *old, int *i)
{
	int	words;
	int	word_len;

	*i = 0;
	words = 0;
	word_len = ft_strlen(old);
	while (str[*i])
	{
		if (ft_strstr(&str[*i], old) == &str[*i])
		{
			words++;
			*i += word_len - 1;
		}
		*i += 1;
	}
	return (words);
}

char	*ft_replace(char *str, char *old, char *new)
{
	int		i;
	int		words;
	char	*result;

	if (old == NULL || new == NULL)
		return (NULL);
	words = get_words(str, old, &i);
	result = malloc(i + words * (ft_strlen(new) - ft_strlen(old)) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (ft_strstr(str, old) == str)
		{
			ft_strcpy(&result[i], new);
			i += ft_strlen(new);
			str += ft_strlen(old);
		}
		else
			result[i++] = *str++;
	}
	result[i] = '\0';
	return (result);
}
