/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexdi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/08/06 17:34:05 by gtraiman          #+#    #+#             */
/*   Updated: 2024/08/06 17:34:05 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	makeapipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	openfd(t_openfile *inout)
{
	inout->infile_fd = open(inout->argv[1], O_RDONLY);
	if (inout->infile_fd == -1)
	{
		perror("open");
		return (-1);
	}
	inout->outfile_fd = open(inout->argv[inout->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inout->outfile_fd == -1)
	{
		close(inout->infile_fd);
		perror("open");
		return (-1);
	}
	return (0);
}

int	ifdup(t_openfile inout, int *pipefd, int i)
{
	if (i == 2)
	{
		dup2(inout.infile_fd, STDIN_FILENO);
		close(inout.infile_fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	close(pipefd[1]);
	if (inout.infile_fd > 2)
		close(inout.infile_fd);
	if (inout.outfile_fd > 2)
		close(inout.outfile_fd);
	return (0);
}

int	dup_in(pid_t *pid, t_openfile *inout, int i, char **envp, int ppipefd[2])
{
	int	pipefd[2];

	if (makeapipe(pipefd) == -1)
		return (-1);
	ppipefd[0] = pipefd[0];
	ppipefd[1] = pipefd[1];
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		close(inout->infile_fd);
		close(inout->outfile_fd);
		dblclose(pipefd);
		return (-1);
	}
	if (*pid == 0)
	{
		write(2, "lalala\n", 7);
		ifdup(*inout, pipefd, i);
		dblclose(ppipefd);
		if (ft_exec(inout->argv[i], envp) == -1)
			return (-1);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[1]);
	return (0);
}

int	last_dup(t_openfile *inout, int i, char **envp, int pipefd[2])
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	dup2(inout->outfile_fd, STDOUT_FILENO);
	close(inout->outfile_fd);
	close(inout->infile_fd);
	if (ft_exec(inout->argv[i], envp) == -1)
	{
		perror("execve");
		return (-1);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	all_dup(t_openfile inout, char **envp)
{
	pid_t pid;
	int i;
	int ppipefd[2];

	i = 2;
	while (i < inout.argc - 2)
	{
		if (dup_in(&pid, &inout, i, envp, ppipefd) == -1)
			return (-1);
		i++;
	}
	if (last_dup(&inout, i, envp, ppipefd) == -1)
		return (-1);
	close(ppipefd[0]);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	pid_t pid;
	t_openfile inout;

	inout.argc = ac;
	inout.argv = av;
	if (ac < 5)
		return (0);
	if (!envp)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (openfd(&inout) == -1)
			exit(EXIT_FAILURE);
		if (all_dup(inout, envp) == -1)
			exit(EXIT_FAILURE);
		close(inout.infile_fd);
		close(inout.outfile_fd);
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
