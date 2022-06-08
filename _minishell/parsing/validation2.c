/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp(str, "|") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

int	contains_operator(char *strarr)
{
	if (ft_strstr(strarr, "|") != NULL
		|| ft_strstr(strarr, "<") != NULL || ft_strstr(strarr, "<<") != NULL
		|| ft_strstr(strarr, ">") != NULL || ft_strstr(strarr, ">>") != NULL)
		return (1);
	return (0);
}

int	check_order(char **strarr)
{
	int	pipes;

	pipes = 1;
	if (is_operator(*strarr))
		return (-4);
	while (*strarr)
	{
		if (pipes == 1 && (ft_strcmp(*strarr, "<") == 0
				|| ft_strcmp(*strarr, "<<") == 0
				|| ft_strcmp(*strarr, ">") == 0
				|| ft_strcmp(*strarr, ">>") == 0))
			pipes = 0;
		else if (pipes == 0 && ft_strcmp(*strarr, "|") == 0)
			return (-1);
		if (!is_operator(*strarr) && (contains_operator(*strarr)))
			return (-2);
		if (is_operator(*strarr) && (*(strarr + 1) == NULL
				|| is_operator(*(strarr + 1))))
			return (-3);
		strarr = strarr + 1;
	}
	return (1);
}

int	print_errors(int err)
{
	if (err == -1)
		printf("Пайпы должны идти до редиректов!\n");
	else if (err == -2)
		printf("Операторы должны разделяться пробелом!\n");
	else if (err == -3)
		printf("Повторяющиеся операторы или оператор без аргумента!\n");
	else if (err == -4)
		printf("Нельзя начать с оператора!\n");
	else
		return (1);
	return (0);
}

int	validate(char **strarr)
{
	return (print_errors(check_order(strarr)));
}
