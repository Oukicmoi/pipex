/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:25:28 by gtraiman          #+#    #+#             */
/*   Updated: 2024/09/02 15:34:12 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct openfile
{
	int		infile_fd;
	int		outfile_fd;
	int		argc;
	char	**argv;
	int		i;
}					t_openfile;

char	**ft_get_path(char **envp);
int		ft_access(char **tab, char *avi, char **PATH);
int		ft_exec(char *argi, char **envp);
int		main(int ac, char **av, char **envp);
void	dblclose(int	*pipe);
int		dblclosin(t_openfile *inout);
int		openfd(t_openfile *inout);
int		makeapipe(int *pipefd);
int		dup_in(pid_t *pid, t_openfile *inout, char **envp, int ppipefd[2]);
int		last_dup(t_openfile *inout, int i, char **envp, int tabpid[]);
int		all_dup(t_openfile inout, char **envp, int tabpid[]);
int		ifdup(t_openfile inout, int *pipefd, int i);
int		waitprocess(int	*tabpid, t_openfile *inout);

#endif