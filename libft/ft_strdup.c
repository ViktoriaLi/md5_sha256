/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:29:00 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/02 19:41:10 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		i++;
	}
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (s1[j] != 0)
	{
		dest[j] = (char)s1[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
