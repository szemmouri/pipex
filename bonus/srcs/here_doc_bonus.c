/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:19:46 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/03 11:08:09 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	here_doc(char *limiter)
{
	char	*line;
	int		fd;

	if (!limiter)
		return (0);
	if (access("/tmp/here_doc", F_OK) == 0)
		unlink("/tmp/here_doc");
	fd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (perror("open"), exit(EXIT_FAILURE), 0);
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	return (close(fd), free(limiter), get_next_line(-1), 1);
}
