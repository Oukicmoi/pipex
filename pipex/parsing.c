/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:26:59 by gtraiman          #+#    #+#             */
/*   Updated: 2024/08/31 17:19:03 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_get_path(char **envp)
{
	char	**tab;
	int		i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
	{
		i++;
	}
	if (!envp[i])
		return (NULL);
	tab = ft_split(&envp[i][5], ':');
	if (!tab)
	{
		perror("ft_split");
		return (NULL);
	}
	return (tab);
}

int	ft_access(char **tab, char *avi, char **path)
{
	int		j;
	char	*temp;

	j = 0;
	while (tab[j])
	{
		temp = ft_strjoin(tab[j], "/");
		free(tab[j]);
		tab[j] = ft_strjoin(temp, avi);
		free(temp);
		if (access(tab[j], F_OK) == 0)
		{
			if (access(tab[j], X_OK) == 0)
			{
				*path = tab[j];
				return (1);
			}
		}
		j++;
	}
	return (-1);
}

int	ft_exec(char *argi, char **envp)
{
	char	**tab;
	char	*path;
	char	**cmd;
	int		ret;

	path = NULL;
	tab = ft_get_path(envp);
	if (!tab)
		return (-1);
	cmd = ft_split(argi, ' ');
	if (!cmd)
	{
		free_split(tab);
		return (-1);
	}
	ret = ft_access(tab, cmd[0], &path);
	if (ret == 1)
	{
		execve(path, cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free_split(cmd);
	free_split(tab);
	return (-1);
}

void	dblclose(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}
