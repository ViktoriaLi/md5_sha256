/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:56:41 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/10 18:59:54 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	round1_1_func(t_addition *iters, int i, int tmp)
{
	const unsigned int	table[16] = {0xd76aa478, 0xe8c7b756, 0x242070db,
	0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
	0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
	0x49b40821};
	const int			s[16] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
	12, 17, 22};

	if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		(*iters).c0 += (((*iters).d0 & (*iters).a0) | (~(*iters).d0 &
		(*iters).b0)) + tmp + table[i];
		md5_cycle_shift(&iters->c0, s[i], 3, iters);
		(*iters).c0 += (*iters).d0;
	}
	if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		(*iters).b0 += (((*iters).c0 & (*iters).d0) | (~(*iters).c0 &
		(*iters).a0)) + tmp + table[i];
		md5_cycle_shift(&iters->b0, s[i], 2, iters);
		(*iters).b0 += (*iters).c0;
	}
}

void	round1_func(t_args *params, t_addition *iters, int i, int iflast)
{
	unsigned int		tmp;
	const unsigned int	table[16] = {0xd76aa478, 0xe8c7b756, 0x242070db,
	0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8,
	0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
	0x49b40821};
	const int			s[16] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22 };

	(*iters).k = i * 4 + 3;
	tmp = make_word_md5(i, params, iflast, iters);
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		(*iters).a0 += (((*iters).b0 & (*iters).c0) | (~(*iters).b0 &
		(*iters).d0)) + tmp + table[i];
		md5_cycle_shift(&iters->a0, s[i], 1, iters);
		(*iters).a0 += (*iters).b0;
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		(*iters).d0 += (((*iters).a0 & (*iters).b0) | (~(*iters).a0 &
		(*iters).c0)) + tmp + table[i];
		md5_cycle_shift(&iters->d0, s[i], 4, iters);
		(*iters).d0 += (*iters).a0;
	}
	round1_1_func(iters, i, tmp);
}

void	round2_func(t_args *params, t_addition *iters, int i, int iflast)
{
	unsigned int		tmp;
	const unsigned int	table[16] = {0xf61e2562, 0xc040b340, 0, 0, 0xd62f105d,
	0x02441453, 0, 0, 0x21e1cde6, 0xc33707d6, 0, 0, 0xa9e3e905, 0xfcefa3f8};
	const int			s[16] = {5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	5, 9, 14, 20 };
	const int			index[16] = {1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13,
	2, 7, 12};

	(*iters).k = index[i] * 4 + 3;
	tmp = make_word_md5(i, params, iflast, iters);
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		(*iters).a0 += (((*iters).b0 & (*iters).d0) | ((*iters).c0 &
		~(*iters).d0)) + tmp + table[i];
		md5_cycle_shift(&iters->a0, s[i], 1, iters);
		(*iters).a0 += (*iters).b0;
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		(*iters).d0 += (((*iters).a0 & (*iters).c0) | ((*iters).b0 &
		~(*iters).c0)) + tmp + table[i];
		md5_cycle_shift(&iters->d0, s[i], 4, iters);
		(*iters).d0 += (*iters).a0;
	}
	round2_1_func(iters, i, tmp);
}

void	finish_md5(t_args *params, t_addition *iters, int iflast)
{
	int i;

	i = 0;
	while (i < 16)
	{
		round3_func(params, iters, i, iflast);
		i++;
	}
	i = 0;
	while (i < 16)
	{
		round4_func(params, iters, i, iflast);
		i++;
	}
	(*iters).a0 += (*iters).a1;
	(*iters).b0 += (*iters).b1;
	(*iters).c0 += (*iters).c1;
	(*iters).d0 += (*iters).d1;
}

void	start_md5(t_args *params, t_addition *iters, int iflast)
{
	int i;

	i = 0;
	clear_iterators(iters);
	(*iters).a1 = (*iters).a0;
	(*iters).b1 = (*iters).b0;
	(*iters).c1 = (*iters).c0;
	(*iters).d1 = (*iters).d0;
	while (i < 16)
	{
		round1_func(params, iters, i, iflast);
		i++;
	}
	i = 0;
	while (i < 16)
	{
		round2_func(params, iters, i, iflast);
		i++;
	}
	i = 0;
	finish_md5(params, iters, iflast);
}
