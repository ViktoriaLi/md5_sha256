/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:12:22 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/09 18:25:49 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

unsigned long long	cycle_shift(unsigned long long nbr, int count, int len)
{
	return (nbr >> count) | (nbr << (len - count));
}

void				main_sha256_funcs(t_addition *iters, t_sha256 *sha_add_vars,
int i, unsigned int *words)
{
	const unsigned int square[64] = {0x428A2F98, 0x71374491, 0xB5C0FBCF,
	0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5, 0xD807AA98,
	0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7,
	0xC19BF174, 0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F,
	0x4A7484AA, 0x5CB0A9DC, 0x76F988DA, 0x983E5152, 0xA831C66D, 0xB00327C8,
	0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967, 0x27B70A85,
	0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E,
	0x92722C85, 0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819,
	0xD6990624, 0xF40E3585, 0x106AA070, 0x19A4C116, 0x1E376C08, 0x2748774C,
	0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3, 0x748F82EE,
	0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7,
	0xC67178F2};

	(*sha_add_vars).eps0 = cycle_shift((*iters).a1, 2, 32) ^
		cycle_shift((*iters).a1, 13, 32) ^ cycle_shift((*iters).a1, 22, 32);
	(*sha_add_vars).ma = ((*iters).a1 & (*iters).b1) ^ ((*iters).a1 &
		(*iters).c1) ^ ((*iters).b1 & (*iters).c1);
	(*sha_add_vars).t2 = (*sha_add_vars).eps0 + (*sha_add_vars).ma;
	(*sha_add_vars).eps1 = cycle_shift((*iters).e1, 6, 32) ^
		cycle_shift((*iters).e1, 11, 32) ^ cycle_shift((*iters).e1, 25, 32);
	(*sha_add_vars).ch = ((*iters).e1 & (*iters).f1) ^ ((~(*iters).e1) &
		(*iters).g1);
	(*sha_add_vars).t1 = (*iters).h1 + (*sha_add_vars).eps1 + (*sha_add_vars).ch
		+ square[i] + words[i];
}

void				start_sha256(t_args *params, t_addition *iters, int iflast)
{
	t_addition				count;
	t_sha256				sha_add_vars;
  unsigned int words[64];

	clear_iterators(&count);
	while (count.i < 16)
	{
		if ((*params).md5_buf[63] == 0 && count.i == 15 && !iflast)
		words[count.i] = (*params).bytes_read * 8;
		else
		words[count.i] = (((((*params).md5_buf[count.k++] << 24) & 4294967295) +
			(((*params).md5_buf[count.k++] << 16) & 16777215)
+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
		count.i++;
	}
	while (count.i < 64)
	{
		sha_add_vars.s0 = cycle_shift(words[count.i-15], 7, 32) ^ cycle_shift(words[count.i-15], 18, 32)
		^ (words[count.i-15] >> 3);
sha_add_vars.s1 = cycle_shift(words[count.i-2], 17, 32) ^ cycle_shift(words[count.i-2], 19, 32) ^ (words[count.i-2] >> 10);
		words[count.i] = words[count.i-16] + sha_add_vars.s0 + words[count.i-7] + sha_add_vars.s1;
		count.i++;
	}
	(*iters).a1 = (*iters).a0;
	(*iters).b1 = (*iters).b0;
	(*iters).c1 = (*iters).c0;
	(*iters).d1 = (*iters).d0;
	(*iters).e1 = (*iters).e0;
	(*iters).f1 = (*iters).f0;
	(*iters).g1 = (*iters).g0;
	(*iters).h1 = (*iters).h0;
	//ft_printf("START%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
	//(*iters).f1, (*iters).h1);

	count.i = 0;
	while (count.i < 64)
	{
		//ft_printf("FFF%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
		//(*iters).f1, (*iters).h1);
    main_sha256_funcs(iters, &sha_add_vars, count.i, words);
    (*iters).h1 = (*iters).g1;
    (*iters).g1 = (*iters).f1;
    (*iters).f1 = (*iters).e1;
    (*iters).e1 = (*iters).d1 + sha_add_vars.t1;
    (*iters).d1 = (*iters).c1;
    (*iters).c1 = (*iters).b1;
    (*iters).b1 = (*iters).a1;
    (*iters).a1 = sha_add_vars.t1 + sha_add_vars.t2;

		//ft_printf("EEE%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
		//(*iters).f1, (*iters).h1);
		count.i++;
	}
		(*iters).a0 += (*iters).a1;
		(*iters).b0 += (*iters).b1;
		(*iters).c0 += (*iters).c1;
		(*iters).d0 += (*iters).d1;
		(*iters).e0 += (*iters).e1;
		(*iters).f0 += (*iters).f1;
		(*iters).g0 += (*iters).g1;
		(*iters).h0 += (*iters).h1;
		//printf("START %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
}
