/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:54:13 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/04 12:54:23 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		res;

	i = 0;
	if (little[i] == 0)
		return (char *)(big);
	while (i < len && big[i] != 0)
	{
		res = i;
		j = 0;
		len = j + len;
		while (i + j < len && big[i + j] == little[j] && little[j] != 0 &&
			big[i + j] != 0)
			j++;
		if (little[j] == 0)
			return (char*)(&big[res]);
		else
			i++;
	}
	return (NULL);
}
