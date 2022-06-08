/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(char *str)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str && *str != ' ')
		{
			while (*str && *str != ' ')
				str++;
			words++;
		}
	}
	return (words);
}

char	*handle_dollar(char *buf, t_data *data)
{
	int		i;
	int		j;
	char	*tmp;
	char 	*buf2;

	i = -1;
	buf2 = ft_strdup(buf);
	while (buf[++i])
	{
		if (buf[i] == '$' && ft_isalnum(buf[i + 1]))
		{
			j = i;
			j++;
			while (ft_isalnum(buf[j]))
				j++;
			tmp = ft_substr(&buf[i], 0, j - i);
			char *tmpval = ft_strdup(get_value(data, tmp + 1));
			if (tmpval == NULL)
				tmpval = ft_strdup("");
			free(buf2);
			buf2 = ft_replace(buf, tmp, tmpval);
			buf = buf2;
			free(tmp);
			free(tmpval);
			i = 0;
		}
	}
	return (buf2);
}

char chose_delim(char *str)
{
	int i;
	char delim;

	i = 0;
	delim = ' ';
	while (str[i])
	{
		if (str[i] == ' ')
			return (delim);
		if (str[i] == '\'' || str[i] == '\"')
			return (str[i]);
		i++;
	}
	return (' ');
}

char	**get_tokens1(char *str, t_data *data)
{
	int		i;
	int		pos;
	int		start;
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!tokens)
		return (NULL);

	i = 0;
	pos = 0;
	start = 0;

	while (str[i])
	{
//		while (str[i] && str[i] == ' ')
//			i++;
		if (str[i] == '\'')
		{
			i++;
			start = i;
			while (str[i] && str[i] != '\'')
				i++;
//			tokens[pos++] = ft_substr(str, start, i - start);
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			start = i;
			while (str[i] && str[i] != '\"')
				i++;
//			tokens[pos++] = ft_substr(str, start, i - start);
			i++;
		}
		else
		{
			start = i;
			while (str[i] && ft_isalnum(str[i]))
				i++;

			char *tmp = ft_substr(str, start, i - start);
			char *new = ft_replace(str, tmp, "SSSSSSS");
			str = new;
//			tokens[pos++] = ft_substr(str, start, i - start);
		}
		printf("%s<\n", str);
	}
	tokens[pos] = NULL;
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (printf("У шелла нет аргументов!\n"));
	if (handle_envp(&data, envp) == F_ALLOC)
		return (0);

//	char **tokens;
//
//	tokens = get_tokens1("\'123\'sss\'456\'", &data);
	get_tokens1("\'aasd\'sadas $HOME sadasd", &data);

//	int i = 0;
//	while (tokens[i] != NULL)
//	{
//		printf("%s\n", tokens[i]);
//		i++;
//	}
}

char	**get_tokens(char *str, t_data *data)
{
	int		i;
	char	**tokens;
	char	delimeter;
	char	*buff;
	char	*token;

	tokens = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	delimeter = ' ';

	delimeter = chose_delim(str);
	token = _ft_strtok (str, &delimeter, &buff);
	while (token != NULL)
	{
//		if (delimeter == '\'')
		printf("%s<\n", buff);
			tokens[i] = ft_strdup(token);
//		else
//			tokens[i] = handle_dollar(token, data);
		delimeter = chose_delim(buff);
//		if (*buff == '\"' && delimeter == ' ')
//			delimeter = '\"';
//		else if (*buff == '\'' && delimeter == ' ')
//			delimeter = '\'';
//		else if (delimeter == '\"' || delimeter == '\'')
//			delimeter = ' ';
		token = _ft_strtok (NULL, &delimeter, &buff);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
