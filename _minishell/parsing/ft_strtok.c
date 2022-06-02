/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strspn(const char *s1, const char *s2)
{
	int	count;

	count = 0;
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
			count++;
		else
			break ;
		s1++;
	}
	return (count);
}

int	ft_strcspn(const char *s1r, const char *s2r)
{
	const char	*s1;
	const char	*s2;

	s1 = s1r;
	while (*s1)
	{
		s2 = s2r;
		while (*s2)
		{
			if (*s1 == *s2++)
				return (s1 - s1r);
		}
		s1++;
	}
	return (s1 - s1r);
}

char	*_ft_strtok(char *string, const char *delim, char **save_ptr)
{
	char	*end;

	if (string == NULL)
		string = *save_ptr;
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}
	string += ft_strspn(string, delim);
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}
	end = string + ft_strcspn(string, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (string);
	}
	*end = '\0';
	*save_ptr = end + 1;
	return (string);
}

char	*ft_strtok(char *s, const char *delim)
{
	static char	*olds;

	return (_ft_strtok (s, delim, &olds));
}
