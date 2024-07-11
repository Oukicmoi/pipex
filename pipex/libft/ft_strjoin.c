/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:58:43 by gtraiman          #+#    #+#             */
/*   Updated: 2023/11/15 19:40:33 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*dest;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dest = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len1)
	{
		dest[i] = s1[i];
		i++;
	}
	while (i < (len2 + len1))
	{
		dest[i] = s2[i - len1];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(void)
{
		printf("%s", ft_strjoin("allez"," les bleus"));
		return(0);
}*/
