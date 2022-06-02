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

int is_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0
			|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
			|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

int validate(char **strarr)
{
	int pipes = 1;

	if (is_operator(*strarr))
	{
		printf("Нельзя начать с оператора!\n");
		return (0);
	}
	while (*strarr)
	{
		if (pipes == 1 && (ft_strcmp(*strarr, "<") == 0 || ft_strcmp(*strarr, "<<") == 0
				|| ft_strcmp(*strarr, ">") == 0 || ft_strcmp(*strarr, ">>") == 0))
		{
			pipes = 0;
		}
		else if (pipes == 0 && ft_strcmp(*strarr, "|") == 0)
		{
			printf("Пайпы должны идти до редиректов!\n");
			return (0);
		}
		if (!is_operator(*strarr) && (ft_strstr(*strarr, "|") != NULL
				|| ft_strstr(*strarr, "<") != NULL || ft_strstr(*strarr, "<<") != NULL
				|| ft_strstr(*strarr, ">") != NULL || ft_strstr(*strarr, ">>") != NULL))
		{
			printf("Операторы должны разделяться пробелом!\n");
			return (0);
		}

		if (is_operator(*strarr) && (*(strarr + 1) == NULL
				|| is_operator(*(strarr + 1))))
		{
			printf("Повторяющиеся операторы или оператор без аргумента!\n");
			return (0);
		}
		*strarr++;
	}
	return (1);
}

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
	int		quote;
	char	*tmp;
	char 	*buf2;

	i = -1;
	quote = 0;
	buf2 = ft_strdup(buf);
	while (buf[++i])
	{
		if (buf[i] == '\'')
			quote++;
		if (buf[i] == '$' && ft_isalnum(buf[i + 1]) && quote != 1)
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
			free(tmp);
			free(tmpval);
			i = 0;
		}
	}
	return (buf2);
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
	token = _ft_strtok (str, &delimeter, &buff);
	while (token != NULL)
	{
		if (delimeter == '\'')
			tokens[i] = ft_strdup(token);
		else
			tokens[i] = handle_dollar(token, data);
		if (*buff == '\"' && delimeter == ' ')
			delimeter = '\"';
		else if (*buff == '\'' && delimeter == ' ')
			delimeter = '\'';
		else if (delimeter == '\"' || delimeter == '\'')
			delimeter = ' ';
		token = _ft_strtok (NULL, &delimeter, &buff);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
