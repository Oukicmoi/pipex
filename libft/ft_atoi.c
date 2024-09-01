/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:55:15 by gtraiman          #+#    #+#             */
/*   Updated: 2023/11/09 17:55:25 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	signe;

	nb = 0;
	signe = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
	{
		++nptr;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			signe *= -1;
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr -48;
		++nptr;
	}
	return (nb * signe);
}
