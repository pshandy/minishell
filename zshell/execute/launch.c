/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c											:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:56:51 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 11:56:52 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	launch_builtin(t_data *data, t_cmd *tmp)
{
	int	tmpin;

	tmpin = -42;
	if (tmp->outfile >= 0)
	{
		tmpin = dup(1);
		dup2(tmp->outfile, 1);
	}
	select_and_exec(tmpin, data, tmp);
	if (tmp->outfile >= 0)
	{
		dup2(tmpin, 1);
		close(tmpin);
	}
}
