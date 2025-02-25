/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:39:42 by szemmour          #+#    #+#             */
/*   Updated: 2025/02/25 12:39:57 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	**create_empty_cmd(void)
{
	char	**empty_cmd;

	empty_cmd = malloc(sizeof(char *));
	if (!empty_cmd)
		return (NULL);
	empty_cmd[0] = NULL;
	return (empty_cmd);
}

static int	is_empty_cmd(const char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static char	*get_subcmd(const char *cmd, int *i)
{
	char	*sub_cmd;
	int		start;

	if (!cmd || !i)
		return (NULL);
	if (cmd[*i] == '\'')
	{
		start = ++(*i);
		while (cmd[*i] && cmd[*i] != '\'')
			(*i)++;
		if (!cmd[*i])
			return (NULL);
		sub_cmd = ft_substr(cmd, start, *i - start);
		(*i)++;
	}
	else
	{
		start = (*i);
		while (cmd[*i] && cmd[*i] != ' ')
			(*i)++;
		sub_cmd = ft_substr(cmd, start, *i - start);
	}
	if (!sub_cmd)
		return (NULL);
	return (sub_cmd);
}

char	**split_cmd(char *cmd)
{
	int		i;
	int		j;
	char	**cmds;

	i = 0;
	j = 0;
	if (!cmd || is_empty_cmd(cmd))
		return (create_empty_cmd());
	cmds = malloc(sizeof(char *) * 50);
	if (!cmds)
		return (ft_putendl_fd("malloc error", 2), NULL);
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (!cmd[i])
			break ;
		cmds[j] = get_subcmd(cmd, &i);
		if (!cmds[j])
			return (free_dstr(cmds), ft_putendl_fd("invalid command format", 2),
				NULL);
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}
