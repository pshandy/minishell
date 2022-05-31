/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:10:34 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:10:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* s - The string from which to create the substring.
* start - The start index of the substring in the string ’s’.
* len - The maximum length of the substring.
*
* Allocates (with malloc(3)) and returns a substring from the string ’s’.
* The substring begins at index ’start’ and is of maximum size ’len’.
*
* Return value The substring. NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*substrc;
	char	*src;
	size_t	length;

	if (!s)
		return (NULL);
	src = (char *)s + start;
	length = 0;
	while (len-- && src[length] != '\0')
		length++;
	if (start >= ft_strlen(s))
		length = 0;
	substr = malloc (length + 1);
	if (substr == NULL)
		return (NULL);
	substrc = substr;
	while (length--)
		*substr++ = *src++;
	*substr = '\0';
	return (substrc);
}
