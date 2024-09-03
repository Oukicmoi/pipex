/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:05:50 by gtraiman          #+#    #+#             */
/*   Updated: 2024/09/03 22:19:34 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ifdup(t_openfile inout, int *pipefd, int i)
{
	close(pipefd[0]);
	if (i == 2)
	{
		dup2(inout.infile_fd, STDIN_FILENO);
		close(inout.infile_fd);
	}
	else
		close(inout.infile_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	return (0);
}

int	dup_in(pid_t *pid, t_openfile *inout, char **envp)
{
	int	pipefd[2];

	if (makeapipe(pipefd) == -1)
		return (-1);
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		dblclosin(inout);
		dblclose(pipefd);
		return (-1);
	}
	if (*pid == 0)
	{
		ifdup(*inout, pipefd, inout->i);
		close(inout->outfile_fd);
		if (ft_exec(inout->argv[inout->i], envp) == -1)
			return (-1);
		exit(EXIT_SUCCESS);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dblclose(pipefd);
	return (0);
}

int	last_dup(t_openfile *inout, int i, char **envp, int tabpid[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(inout->outfile_fd, STDOUT_FILENO);
		close(inout->outfile_fd);
		close(inout->infile_fd);
		if (ft_exec(inout->argv[i], envp) == -1)
		{
			perror("execve");
			return (-1);
		}
		exit(EXIT_SUCCESS);
	}
	tabpid[i - 2] = pid;
	return (0);
}

int	all_dup(t_openfile inout, char **envp, int tabpid[])
{
	pid_t		pid;

	inout.i = 2;
	while (inout.i < inout.argc - 2)
	{
		if (dup_in(&pid, &inout, envp) == -1)
			return (-1);
		tabpid[inout.i - 2] = pid;
		inout.i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int			*tabpid;
	t_openfile	inout;

	inout.argc = ac;
	inout.argv = av;
	if (ac < 5)
		return (0);
	if (!envp)
		return (0);
	if (openfd(&inout) == -1)
		exit(EXIT_FAILURE);
	tabpid = (int *) malloc ((ac - 3) * sizeof (int));
	if (!tabpid)
		return (1);
	if (all_dup(inout, envp, tabpid) == -1)
		exit(EXIT_FAILURE);
	if (last_dup(&inout, ac - 2, envp, tabpid) == -1)
		return (-1);
	close(inout.infile_fd);
	close(inout.outfile_fd);
	close(0);
	waitprocess(tabpid, &inout);
	free(tabpid);
	return (0);
}
