/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:38:39 by szemmour          #+#    #+#             */
/*   Updated: 2025/02/25 12:33:37 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_current_dir(char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	while (envp[i])
	{
		pwd = ft_strnstr(envp[i], "PWD=", ft_strlen(envp[i]));
		if (pwd)
		{
			pwd = ft_strjoin(":", pwd + 4);
			if (!pwd)
				return (NULL);
			return (pwd);
		}
		i++;
	}
	return (NULL);
}

static char	**get_paths(char **envp)
{
	int		i;
	char	*str;
	char	**paths;
	char	*pwd;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		str = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (str)
		{
			pwd = get_current_dir(envp);
			str = ft_strjoin(str, pwd);
			paths = ft_split(str + 5, ':');
			free(str);
			free(pwd);
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	if (!paths || !cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	resolve_cmd_paths(char **envp, t_cmd *cmds)
{
	char	**paths;

	if (!envp || !cmds)
		return (0);
	paths = get_paths(envp);
	if (!paths)
		return (0);
	while (cmds)
	{
		if (cmds->command && cmds->command[0])
			cmds->path = get_cmd_path(paths, cmds->command[0]);
		cmds = cmds->next;
	}
	free_dstr(paths);
	return (1);
}

void	init_vars(t_fd *fd, char *in_paht, char *out_path)
{
	fd->in = open(in_paht, O_RDONLY);
	if (fd->in == -1)
		perror("open");
	fd->out = open(out_path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd->out == -1)
	{
		perror("open");
		close_fds(fd);
		exit(EXIT_FAILURE);
	}
}
