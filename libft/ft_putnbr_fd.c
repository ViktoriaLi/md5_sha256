/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:46:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/10 15:46:38 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void		print_chars(int d, int c, int n, int fd)
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
		write(fd, &res, 1);
		c = c / 10;
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	int		d;
	int		c;

	c = 1;
	if (n == -2147483648)
	{
		d = 147483648;
		n = 147483648;
		write(fd, "-2", 2);
	}
	if (n < 0)
	{
		d = -1 * n;
		n = -1 * n;
		write(fd, "-", 1);
	}
	else
		d = n;
	print_chars(d, c, n, fd);
}
