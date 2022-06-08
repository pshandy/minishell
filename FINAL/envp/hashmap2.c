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

char	**hashmap_to_array()
{
	//TO_DO
}
