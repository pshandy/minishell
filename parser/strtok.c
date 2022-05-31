#include "parser.h"

int ft_strspn (const char *s1, const char *s2)
{
	const char *s = s1;
	const char *c;

	while (*s1)
  	{
	  	for (c = s2; *c; c++)
	  	{
			if (*s1 == *c)
		  	break;
	  	}
	  	if (*c == '\0')
	  		break;
		s1++;
    }
	return s1 - s;
}

int ft_strcspn(const char *s1, const char *s2)
{
	const char *p, *spanp;
	char c, sc;

	for (p = s1;;) {
		c = *p++;
		spanp = s2;
		do {
			if ((sc = *spanp++) == c)
				return (p - 1 - s1);
		} while (sc != 0);
	}
	return (0);
}

char	*_ft_strtok(char *string, const char *delim, char **save_ptr)
{
	char	*end;
	if (string == NULL)
		string = *save_ptr;
	if (*string == '\0')
	{
		*save_ptr = string;
		//printf("%s<1\n", string);
		return (NULL);
	}
		//printf("%s<1111\n", string);
	string += ft_strspn(string, delim);
	if (*string == '\0')
	{
		*save_ptr = string;
		//printf("%s<2\n", string);
		return NULL;
	}
	end = string + ft_strcspn(string, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		//printf("%s<3\n", string);
		return (string);
	}
	*end = '\0';
	*save_ptr = end + 1;

	//printf("%s<\n", string);
	return (string);
}

char *ft_strtok (char *s, const char *delim)
{
	static char *olds;
//	printf("%s<", olds);
	return _ft_strtok (s, delim, &olds);
}
