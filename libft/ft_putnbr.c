/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 17:13:39 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/01 18:33:28 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void		print_chars(int d, int c, int n)
{
	char res;

	res = 0;
	while (d > 9)
	{
		d = d / 10;
		c = c * 10;
	}
	while (c > 0 && n >= 0)
	{
		res = (n / c) % 10 + '0';
		write(1, &res, 1);
		c = c / 10;
	}
}

void			ft_putnbr(int n)
{
	int		d;
	int		c;

	c = 1;
	if (n == -2147483648)
	{
		d = 147483648;
		n = 147483648;
		write(1, "-2", 2);
	}
	if (n < 0)
	{
		d = -1 * n;
		n = -1 * n;
		write(1, "-", 1);
	}
	else
		d = n;
	print_chars(d, c, n);
}
