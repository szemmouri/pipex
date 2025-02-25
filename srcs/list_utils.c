/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:38:42 by szemmour          #+#    #+#             */
/*   Updated: 2025/02/22 11:15:18 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_cmd	*ft_new_cmd(char **command)
{
	t_cmd	*new;

	if (!command)
		return (NULL);
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->command = command;
	new->path = NULL;
	new->pid = -1;
	new->next = NULL;
	return (new);
}

void	push_back(t_cmd **lst, char **command)
{
	t_cmd	*tmp;
	t_cmd	*new;

	if (!lst || !command)
		return ;
	new = ft_new_cmd(command);
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
