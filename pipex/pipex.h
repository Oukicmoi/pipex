/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:25:28 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/11 19:17:43 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft/libft.h"

char	**ft_get_path(char **envp);
int	ft_access(char **tab,char *avi,char **PATH);
int	ft_exec(char *argi, char **envp);
int	main(int ac, char **av, char **envp);



#endif