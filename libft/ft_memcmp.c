/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 15:57:30 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/04 16:26:52 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (n != 0)
	{
		str1 = (unsigned char *)s1;
		str2 = (unsigned char *)s2;
		if (str1[i] == 0 && str2[i] == 0)
			return (0);
		if ((str1[i] == 0 || str2[i] == 0) || n == 0)
			return (str1[i] - str2[i]);
		while (i < n)
		{
			if (str1[i] == str2[i])
				i++;
			else
				return (str1[i] - str2[i]);
		}
	}
	return (0);
}
