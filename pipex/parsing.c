/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:17:41 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/16 16:34:26 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	char		**tab;
	int			i;

	i = 0;
	while (ft_strncmp ("PATH=", envp[i], 5) != 0)
	{
		i++;
	}
	if (envp[i] == 0)
		return (0);
	tab = ft_split(&envp[i][5], ':');
	return (tab);
}

int	ft_access(char **tab, char *avi, char **path)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		tab[j] = ft_strjoin(tab[j], "/");
		tab[j] = ft_strjoin(tab[j], avi);
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
	return (-1); /// erreur fonction inexistqnte
}

int	ft_exec(char *argi, char **envp)
{
	char	**tab;
	char	*path;
	char	**cmd;

	path = NULL;
	tab = ft_get_path(envp);
	cmd = ft_split(argi, ' ');
	if (ft_access(tab, cmd[0], &path) == 1)
	{
		execve(path, cmd, envp);
	}
	else
		return (-1);
	return (0);
}
