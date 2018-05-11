/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:29:49 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/09 13:30:17 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char		*min_int(int n, char *dest)
{
	int		len;

	len = 3;
	n = 214748364;
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	n = 214748364;
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	dest[len--] = '8';
	while (len >= 2)
	{
		dest[len--] = n % 10 + '0';
		n = n / 10;
	}
	dest[len--] = '2';
	dest[len] = '-';
	return (dest);
}

static char		*ft_negative_itoa(int n, char *dest)
{
	long	d;
	int		len;

	len = 2;
	d = -1 * n;
	while (d > 9)
	{
		d = d / 10;
		len++;
	}
	d = -1 * n;
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	while (len)
	{
		dest[len--] = d % 10 + '0';
		d = d / 10;
	}
	dest[len] = '-';
	return (dest);
}

char			*ft_itoa(int n)
{
	long	d;
	int		len;
	char	*dest;

	dest = NULL;
	if (n == -2147483648)
		return (min_int(n, dest));
	if (n < 0 && n != -2147483648)
		return (ft_negative_itoa(n, dest));
	len = 1;
	d = n;
	while (d > 9)
	{
		d = d / 10;
		len++;
	}
	if (!(dest = (char *)malloc((len + 1))))
		return (NULL);
	dest[len--] = 0;
	while (len >= 0)
	{
		dest[len--] = n % 10 + '0';
		n = n / 10;
	}
	return (dest);
}
