/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:10:42 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/18 12:10:43 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ends_with(const char *str, const char *suffix)
{
	int	lenstr;
	int	lensuffix;

	if (!str || !suffix)
		return (0);
	lenstr = ft_strlen(str);
	lensuffix = ft_strlen(suffix);
	if (lensuffix > lenstr)
		return (0);
	return (ft_strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0);
}

void	change_lvl(t_data *data, char *str)
{
	int		prev;
	char	*str1;
	char	*str2;
	char	*shlvl;

	shlvl = get_value(data, "SHLVL");
	if (shlvl == NULL)
		ft_export(data, "SHLVL=0");
	else if (ends_with(str, "/minishell") || ft_strcmp(str, "minishell") == 0)
	{
		prev = ft_atoi(shlvl);
		str1 = ft_itoa(prev + 1);
		str2 = ft_strjoin("SHLVL=", str1);
		ft_export(data, str2);
		free(str1);
		free(str2);
	}
}
