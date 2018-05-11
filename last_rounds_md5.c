/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_rounds_md5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:23:17 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/10 18:38:57 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	round2_1_func(t_addition *iters, int i, int tmp)
{
	const unsigned int	table[16] = {0xf61e2562, 0xc040b340, 0x265e5a51,
		0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6,
		0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9,
		0x8d2a4c8a};
	const int			s[16] = {5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
		14, 20};

	if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		(*iters).c0 += (((*iters).d0 & (*iters).b0) | ((*iters).a0 &
		~(*iters).b0)) + tmp + table[i];
		md5_cycle_shift(&iters->c0, s[i], iters);
		(*iters).c0 += (*iters).d0;
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		(*iters).b0 += (((*iters).c0 & (*iters).a0) | ((*iters).d0 &
		~(*iters).a0)) + tmp + table[i];
		md5_cycle_shift(&iters->b0, s[i], iters);
		(*iters).b0 += (*iters).c0;
	}
}

void	round3_1_func(t_addition *iters, int i, int tmp)
{
	const unsigned int	table[16] = {0xfffa3942, 0x8771f681, 0x6d9d6122,
	0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6,
	0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8,
	0xc4ac5665};
	const int			s[16] = {4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4,
		11, 16, 23};

	if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		(*iters).c0 += ((*iters).d0 ^ (*iters).a0 ^ (*iters).b0) +
		tmp + table[i];
		md5_cycle_shift(&iters->c0, s[i], iters);
		(*iters).c0 += (*iters).d0;
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		(*iters).b0 += ((*iters).c0 ^ (*iters).d0 ^ (*iters).a0)
		+ tmp + table[i];
		md5_cycle_shift(&iters->b0, s[i], iters);
		(*iters).b0 += (*iters).c0;
	}
}

void	round3_func(t_args *params, t_addition *iters, int i, int iflast)
{
	unsigned int		tmp;
	const unsigned int	table[16] = {0xfffa3942, 0x8771f681, 0, 0, 0xa4beea44,
	0x4bdecfa9, 0, 0, 0x289b7ec6, 0xeaa127fa, 0, 0, 0xd9d4d039, 0xe6db99e5};
	const int			s[16] = {4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23};
	const int			index[16] = {5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9,
	12, 15, 2};

	(*iters).k = index[i] * 4 + 3;
	tmp = make_word_md5(params, iflast, iters);
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		(*iters).a0 += ((*iters).b0 ^ (*iters).c0 ^ (*iters).d0) +
		tmp + table[i];
		md5_cycle_shift(&iters->a0, s[i], iters);
		(*iters).a0 += (*iters).b0;
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		(*iters).d0 += ((*iters).a0 ^ (*iters).b0 ^ (*iters).c0) +
		tmp + table[i];
		md5_cycle_shift(&iters->d0, s[i], iters);
		(*iters).d0 += (*iters).a0;
	}
	round3_1_func(iters, i, tmp);
}

void	round4_1_func(t_addition *iters, int i, int tmp)
{
	const unsigned int	table[16] = {0, 0, 0xab9423a7, 0xfc93a039, 0,
	0, 0xffeff47d, 0x85845dd1, 0, 0, 0xa3014314, 0x4e0811a1, 0, 0,
	0x2ad7d2bb, 0xeb86d391};
	const int			s[16] = {6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21};

	if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		(*iters).c0 += ((*iters).a0 ^ ((*iters).d0 | ~(*iters).b0)) +
		tmp + table[i];
		md5_cycle_shift(&iters->c0, s[i], iters);
		(*iters).c0 += (*iters).d0;
	}
	if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		(*iters).b0 += ((*iters).d0 ^ ((*iters).c0 | ~(*iters).a0)) +
		tmp + table[i];
		md5_cycle_shift(&iters->b0, s[i], iters);
		(*iters).b0 += (*iters).c0;
	}
}

void	round4_func(t_args *params, t_addition *iters, int i, int iflast)
{
	unsigned int		tmp;
	const unsigned int	table[16] = {0xf4292244, 0x432aff97, 0, 0, 0x655b59c3,
	0x8f0ccc92, 0, 0, 0x6fa87e4f, 0xfe2ce6e0, 0, 0, 0xf7537e82, 0xbd3af235};
	const int			s[16] = {6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21};
	const int			index[16] = {0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13,
	4, 11, 2, 9};

	(*iters).k = index[i] * 4 + 3;
	tmp = make_word_md5(params, iflast, iters);
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		(*iters).a0 += ((*iters).c0 ^ ((*iters).b0 | ~(*iters).d0)) +
		tmp + table[i];
		md5_cycle_shift(&iters->a0, s[i], iters);
		(*iters).a0 += (*iters).b0;
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		(*iters).d0 += ((*iters).b0 ^ ((*iters).a0 | ~(*iters).c0)) +
		tmp + table[i];
		md5_cycle_shift(&iters->d0, s[i], iters);
		(*iters).d0 += (*iters).a0;
	}
	round4_1_func(iters, i, tmp);
}
