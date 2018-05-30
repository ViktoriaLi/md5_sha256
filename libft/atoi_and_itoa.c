/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_and_itoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 15:48:45 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 15:50:28 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static char		*ft_negative_itoa(intmax_t n, char *dest)
{
	size_t		d;
	intmax_t	len;

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

char			*ft_printf_itoa(intmax_t n)
{
	size_t		d;
	intmax_t	len;
	char		*dest;

	dest = NULL;
	if (n < 0)
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

char			*ft_uns_itoa(uintmax_t n)
{
	uintmax_t	d;
	intmax_t	len;
	char		*dest;

	dest = NULL;
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

static int		main_atoi(const char *str, int i, int sign)
{
	long long	tmp;
	long long	res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res * 10 + sign * (str[i] - '0');
		if (tmp / 10 != res && sign == -1)
			return (0);
		if (tmp / 10 != res && sign == 1)
			return (-1);
		res = tmp;
		i++;
	}
	return (int)(res);
}

int				ft_printf_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (main_atoi(str, i, sign));
}
