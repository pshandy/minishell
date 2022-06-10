/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:10:42 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/18 12:10:43 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_fork;

static int is_number(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_data *data, char **args)
{
	unsigned char	ret;

	ret = 0;
	if (args[1] && is_number(args[1]))
		ret = ft_atoi(args[1]);
	else if (args[1] && !is_number(args[1]))
		ret = 2;
	if (g_fork == 0)
	{
		ft_putstr_fd("exit\n", 1);
		data->exit_code = ret;
		exit((int)ret);
	}
	ft_putstr_fd("exit\n", 1);
	token_lstclear(&(data->head));
	cmd_lstclear(&(data->cmds));
	free_hashmap(data);
	exit((int)ret);
}
