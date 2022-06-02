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

void	show_entry(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->hashmap_size)
	{
		if (!(&data->hashmap[i]->next == &data->hashmap[i]
				&& &data->hashmap[i]->prev == &data->hashmap[i]))
			print_list(&data->hashmap[i]);
		i++;
	}
}

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
