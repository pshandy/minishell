/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_hashmap(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->hashmap_size)
	{
		_ft_lstclear(&data->hashmap[i]);
		i++;
	}
	free(data->hashmap);
}

char	**hashmap_to_array(t_data *data)
{
	int			i;
	char		**arr;
	char		*str;
	char		*t;
	t_hashmap	*tmp;


	i = 0;
	arr = NULL;
	while (i < data->hashmap_size)
	{
		if (!(&data->hashmap[i]->next == &data->hashmap[i]
				&& &data->hashmap[i]->prev == &data->hashmap[i]))
		{
			tmp = data->hashmap[i]->next;
			while (tmp != data->hashmap[i])
			{
				t = ft_strjoin(tmp->key, "=");
				str = ft_strjoin(t, tmp->value);
				free(t);
				arr = add_str(arr, str);
				tmp = tmp->next;
			}
		}
		i++;
	}
	return (arr);
}
