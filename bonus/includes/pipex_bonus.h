/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:38:47 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/03 10:45:10 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_fd
{
	int				in;
	int				out;
	int				fd[2];
}					t_fd;

typedef struct s_cmd
{
	char			**command;
	char			*path;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

// ================= Parsing Commands ==================
char				**split_cmd(char *cmd);

// ==================== Error utils ====================
void				free_dstr(char **cmds);
void				free_cmds(t_cmd *cmds);
void				close_fds(t_fd *fd);
void				put_perror(char *msg, t_fd *fd, t_cmd *cmds);

// ==================== Pipex utils ====================
int					resolve_cmd_paths(char **envp, t_cmd *cmds);
void				init_vars(t_fd *fd, char *in_paht, char *out_path);
void				dup_file(t_fd *fd_t, int fd);

// ==================== List utils ====================
void				push_back(t_cmd **lst, char **command);

// ================= Here_doc =========================
int					here_doc(char *limiter);

#endif