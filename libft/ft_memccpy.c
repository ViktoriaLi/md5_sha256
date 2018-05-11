/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:39:53 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/02 15:03:26 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst1;
	unsigned char	*src1;

	i = 0;
	if (n != 0)
	{
		src1 = (unsigned char *)src;
		dst1 = (unsigned char *)dst;
		while (i < n && src1[i] != (unsigned char)c)
		{
			dst1[i] = src1[i];
			i++;
		}
		if (i < n && src1[i] == (unsigned char)c)
		{
			dst1[i] = src1[i];
			dst = (void *)dst1;
			return (dst + i + 1);
		}
	}
	return (NULL);
}
