/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                         :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:10:42 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/18 12:10:43 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_letter(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_export(t_data *data, char *str)
{
	char		**strarr;
	t_hashmap	*tmp;

	if (!str || ft_strchr(str, '=') == 0)
		return (1);
	strarr = ft_split2(str, '=');
	if (!is_letter(strarr[0]))
	{
		perror("Ошибка в значении ключа!\n");
		free(strarr[0]);
		free(strarr[1]);
		free(strarr);
		return (1);
	}
	tmp = get_record(data, strarr[0]);
	if (tmp == NULL)
		add_to_hashmap(data, strarr[0], strarr[1]);
	else
	{
		tmp->value = strarr[1];
		free(strarr[0]);
	}
	free(strarr);
	return (0);
}
