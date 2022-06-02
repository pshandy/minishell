/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_hash(char *str)
{
	int	hash;

	hash = 0;
	while (*str)
		hash += *str++;
	return (hash);
}

int	init_hashmap(t_data *data, int size)
{
	int			i;
	t_hashmap	**hashmap;

	data->hashmap_size = size;
	hashmap = malloc(sizeof(t_hashmap *) * data->hashmap_size);
	if (!hashmap)
		return (F_ALLOC);
	i = 0;
	while (i < (data->hashmap_size))
	{
		if (_ft_lstinit(&hashmap[i]) == F_ALLOC)
			return (F_ALLOC);
		i++;
	}
	data->hashmap = hashmap;
	return (1);
}

int	add_to_hashmap(t_data *data, char *key, char *value)
{
	int	hash_code;

	hash_code = get_hash(key) % data->hashmap_size;
	if (_ft_lstadd_back(&data->hashmap[hash_code], key, value) == F_ALLOC)
		return (F_ALLOC);
	return (1);
}

int	del_from_hashmap(t_data *data, char *key)
{
	int	hash_code;

	hash_code = get_hash(key) % data->hashmap_size;
	if (_ft_lstdel(&data->hashmap[hash_code], key) == 0)
		return (0);
	return (1);
}

char	*get_value(t_data *data, char *key)
{
	t_hashmap	*current;
	int			hash_code;

	hash_code = get_hash(key) % data->hashmap_size;
	current = (data->hashmap[hash_code])->next;
	while (current != data->hashmap[hash_code])
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
