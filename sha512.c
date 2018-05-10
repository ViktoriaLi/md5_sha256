/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 15:28:57 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/10 16:54:42 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

void	main_sha512_funcs(t_addition *iters, t_sha512_vars *add_vars,
unsigned long long *words, unsigned long long *square)
{
	square[67] = 0xf57d4f7fee6ed178;
	square[68] = 0x06f067aa72176fba;
	square[69] = 0x0a637dc5a2c898a6;
	square[70] = 0x113f9804bef90dae;
	square[71] = 0x1b710b35131c471b;
	square[72] = 0x28db77f523047d84;
	square[73] = 0x32caab7b40c72493;
	square[74] = 0x3c9ebe0a15c9bebc;
	square[75] = 0x431d67c49c100d4c;
	square[76] = 0x4cc5d4becb3e42b6;
	square[77] = 0x597f299cfc657e2a;
	square[78] = 0x5fcb6fab3ad6faec;
	square[79] = 0x6c44198c4a475817;
	(*add_vars).eps0 = cycle_shift((*iters).aa1, 28, 64) ^
	cycle_shift((*iters).aa1, 34, 64) ^ cycle_shift((*iters).aa1,
	39, 64);
	(*add_vars).ma = ((*iters).aa1 & (*iters).bb1) ^ ((*iters).aa1 &
	(*iters).cc1) ^ ((*iters).bb1 & (*iters).cc1);
	(*add_vars).t2 = (*add_vars).eps0 + (*add_vars).ma;
	(*add_vars).eps1 = cycle_shift((*iters).ee1, 14, 64) ^
	cycle_shift((*iters).ee1, 18, 64) ^ cycle_shift((*iters).ee1, 41, 64);
	(*add_vars).ch = ((*iters).ee1 & (*iters).ff1) ^ ((~((*iters).ee1)) &
	(*iters).gg1);
	(*add_vars).t1 = (*iters).hh1 + (*add_vars).eps1 + (*add_vars).ch +
	square[(*iters).i] + words[(*iters).i];
}

void	create_consts(t_addition *iters, t_sha512_vars *add_vars,
unsigned long long *words)
{
	static unsigned long long square[80] = {0x428a2f98d728ae22,
		0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
		0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b,
		0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
		0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f,
		0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
		0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5,
		0x240ca1cc77ac9c65, 0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
		0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
		0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
		0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f,
		0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926,
		0x4d2c6dfc5ac42aed, 0x53380d139d95b3df, 0x650a73548baf63de,
		0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
		0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791,
		0xc76c51a30654be30, 0xd192e819d6ef5218, 0xd69906245565a910,
		0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8,
		0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
		0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
		0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60,
		0x84c87814a1f0ab72, 0x8cc702081a6439ec, 0x90befffa23631e28,
		0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
		0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e};

	main_sha512_funcs(iters, add_vars, words, square);
}

void	fill_add_words_512(unsigned long long *words,
t_sha512_vars *add_vars, t_addition *iters)
{
	(*add_vars).s0 = cycle_shift(words[(*iters).i - 15], 1, 64) ^
	cycle_shift(words[(*iters).i - 15], 8, 64) ^
	(words[(*iters).i - 15] >> 7);
	(*add_vars).s1 = cycle_shift(words[(*iters).i - 2], 19, 64) ^
	cycle_shift(words[(*iters).i - 2], 61, 64) ^
	(words[(*iters).i - 2] >> 6);
}

void	main_512_cycle(t_addition *iters, unsigned long long *words,
t_sha512_vars *add_vars)
{
	(*iters).aa1 = (*iters).aa0;
	(*iters).bb1 = (*iters).bb0;
	(*iters).cc1 = (*iters).cc0;
	(*iters).dd1 = (*iters).dd0;
	(*iters).ee1 = (*iters).ee0;
	(*iters).ff1 = (*iters).ff0;
	(*iters).gg1 = (*iters).gg0;
	(*iters).hh1 = (*iters).hh0;
	(*iters).i = 0;
	while ((*iters).i < 80)
	{
		create_consts(iters, add_vars, words);
		(*iters).hh1 = (*iters).gg1;
		(*iters).gg1 = (*iters).ff1;
		(*iters).ff1 = (*iters).ee1;
		(*iters).ee1 = (*iters).dd1 + (*add_vars).t1;
		(*iters).dd1 = (*iters).cc1;
		(*iters).cc1 = (*iters).bb1;
		(*iters).bb1 = (*iters).aa1;
		(*iters).aa1 = (*add_vars).t1 + (*add_vars).t2;
		(*iters).i++;
	}
	(*iters).aa0 += (*iters).aa1;
	(*iters).bb0 += (*iters).bb1;
}

void	start_sha512(t_args *params, t_addition *iters, int iflast)
{
	t_sha512_vars		add_vars;
	unsigned long long	words[80];

	clear_iterators(iters);
	while ((*iters).i < 16)
	{
		if ((*params).md5_buf[127] == 0 && (*iters).i == 15 && !iflast)
			words[(*iters).i++] = (*params).bytes_read * 8;
		else
			words[(*iters).i++] = made_words_for_sha512(params, iters);
	}
	while ((*iters).i < 80)
	{
		fill_add_words_512(words, &add_vars, iters);
		words[(*iters).i] = words[(*iters).i - 16] + add_vars.s0 +
		words[(*iters).i - 7] + add_vars.s1;
		(*iters).i++;
	}
	main_512_cycle(iters, words, &add_vars);
	(*iters).cc0 += (*iters).cc1;
	(*iters).dd0 += (*iters).dd1;
	(*iters).ee0 += (*iters).ee1;
	(*iters).ff0 += (*iters).ff1;
	(*iters).gg0 += (*iters).gg1;
	(*iters).hh0 += (*iters).hh1;
}
