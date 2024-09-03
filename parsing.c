/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:26:59 by gtraiman          #+#    #+#             */
/*   Updated: 2024/09/03 19:10:42 by gtraiman         ###   ########.fr       */
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
	int			j;
	char		*temp;

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
	t_execstr	ex;

	ex.path = NULL;
	ex.tab = ft_get_path(envp);
	if (!ex.tab)
		return (-1);
	ex.cmd = ft_split(argi, ' ');
	if (!ex.cmd)
	{
		free_split(ex.tab);
		return (-1);
	}
	ex.ret = ft_access(ex.tab, ex.cmd[0], &ex.path);
	ex.i = -1;
	if (argi[0] == '/')
	{
		if (access (argi, R_OK) == 0)
		{
			while ((ft_split (argi, '/'))[ex.i + 1])
				ex.i++;
			execve (argi, &(ft_split(argi, '/'))[ex.i], envp);
		}
	}
	execfinal(ex, envp);
	return (0);
}

int	execfinal(t_execstr ex, char **envp)
{
	if (ex.ret == 1 && ex.i != -1)
	{
		execve(ex.path, ex.cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free_split(ex.cmd);
	free_split(ex.tab);
	return (0);
}
