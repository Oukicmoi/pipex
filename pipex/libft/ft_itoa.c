/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:01:28 by gtraiman          #+#    #+#             */
/*   Updated: 2023/11/13 16:45:12 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_while1(int n, char *dest, int *i)
{
	while (dest[*i])
		(*i)++;
	dest[*i] = n + 48;
}

static void	ft_itoa_recursive(int n, char *dest, int *i)
{
	if (n < 0)
	{
		dest[0] = '-';
		n = -n;
		*i = 1;
	}
	if (n > 9)
		ft_itoa_recursive(n / 10, dest, i);
	ft_while1(n % 10, dest, i);
}

static void	ft_szcall(int *j, int n)
{
	j[0] = 1;
	if (n < 0)
	{
		n = -n;
		j[0]++;
	}
	while (n > 9)
	{
		j[0]++;
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	int		j[1];
	int		i;
	char	*dest;

	ft_szcall(j, n);
	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	dest = (char *)ft_calloc(j[0] + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	ft_itoa_recursive(n, dest, &i);
	dest[i + 1] = '\0';
	return (dest);
}

/*
int	main(void)
{
		printf("%s", ft_itoa(-227829));
		return (0);
}
*/