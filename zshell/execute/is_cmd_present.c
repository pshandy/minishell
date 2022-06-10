/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd_present.c									:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:56:51 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 11:56:52 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_mypath(char **mypath)
{
	int	it;

	it = -1;
	if (!mypath)
		return ;
	while (mypath[++it])
		free(mypath[it]);
	free(mypath);
}

static char	**get_path_array(t_data *data)
{
	int		i;
	char	*tmp;
	char	**mypath;

	mypath = ft_split(get_value(data, "PATH"), ':');
	i = -1;
	while (mypath[++i])
	{
		tmp = mypath[i];
		mypath[i] = ft_strjoin(mypath[i], "/");
		free(tmp);
	}
	return (mypath);
}

char	*is_cmd_present(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**mypath;
	char	*_cmd;

	if (access(cmd->args[0], F_OK) == 0)
		return (cmd->args[0]);
	mypath = get_path_array(data);
	i = -1;
	while (mypath && mypath[++i])
	{
		_cmd = ft_strjoin(mypath[i], cmd->args[0]);
		if (access(_cmd, F_OK) == 0)
		{
			free_mypath(mypath);
			return (_cmd);
		}
		free(_cmd);
	}
	free_mypath(mypath);
	return (NULL);
}
