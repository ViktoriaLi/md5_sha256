/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 16:37:16 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/04 17:00:52 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t k;

	k = 0;
	i = 0;
	j = ft_strlen(src);
	if (size <= ft_strlen(dst))
		return (j + size);
	while (i < size - 1 && dst[i] != 0)
		i++;
	j += i;
	while (i < size - 1 && src[k] != 0)
	{
		dst[i] = src[k];
		i++;
		k++;
	}
	dst[i] = 0;
	return (j);
}
