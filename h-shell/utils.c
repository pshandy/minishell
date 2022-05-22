#include "./includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (*end != '\0')
		end++;
	return (end - str);
}

static size_t	getlen(const char *t, char c)
{
	size_t	i;

	i = 0;
	while (t[i] != c && t[i] != '\0')
		i++;
	return (i);
}

static size_t	getsize(const char *s, char c)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			size++;
		i++;
	}
	return (size + 1);
}

static char	**ft_clear(char **str, int j)
{
	while (j)
	{
		free(str[j]);
		j--;
	}
	return (NULL);
}

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

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	str = (char **)malloc((sizeof(char *) * getsize(s, c)));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			str[j] = ft_substr(&s[i], 0, getlen(&s[i], c));
			if (str[j] == NULL)
				return (ft_clear(str, j));
			j++;
		}
		i++;
	}
	str[j] = NULL;
	return (str);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	if (src == NULL && dest == NULL)
		return (NULL);
	s = (const char *)src;
	d = (char *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*result;

	size = ft_strlen(s) + 1;
	result = malloc(size);
	if (result == 0)
		return (0);
	return ((char *)ft_memcpy(result, s, size));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*strc;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	strc = str;
	while (*s1 != '\0')
		*str++ = *s1++;
	while (*s2 != '\0')
		*str++ = *s2++;
	*str = '\0';
	return (strc);
}



