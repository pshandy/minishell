/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:10:42 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/18 12:10:43 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmd_lstinit(t_cmd **cmd_list)
{
	*cmd_list = malloc(sizeof(t_cmd));
	if (cmd_list == NULL)
		return (F_ALLOC);
	(*cmd_list)->cmd = NULL;
	(*cmd_list)->args = NULL;
	(*cmd_list)->infile = -2;
	(*cmd_list)->outfile = -2;
	(*cmd_list)->prev = *cmd_list;
	(*cmd_list)->next = *cmd_list;
	return (1);
}

int	cmd_lstadd_back(t_cmd **cmd_list, t_cmd *cmd)
{
	cmd->prev = (*cmd_list)->prev;
	cmd->next = *cmd_list;
	(*cmd_list)->prev->next = cmd;
	(*cmd_list)->prev = cmd;
	return (1);
}

t_cmd	*cmd_create_elem(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->infile = -1;
	cmd->outfile = -1;
	return (cmd);
}

void	cmd_lstclear(t_cmd **lst)
{
	t_cmd	*tmp;
	t_cmd	*next;

	next = (*lst)->next;
	while (next != *lst)
	{
		tmp = next;
		free(tmp->cmd);
		free(tmp->args[0]);
		free(tmp->args);
		next = next->next;
		free(tmp);
	}
	free(*lst);
}
