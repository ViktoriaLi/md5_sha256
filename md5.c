#include "ft_ssl.h"
#include <stdio.h>

void md5_cycle_shift(t_addition *iters, int count, int rounds)
{
	unsigned int tmp;
	int bits[32];
	//printf("111%d\n", (*iters).a0);
	clear_iterators(iters);
	if (rounds == 1)
		tmp = (*iters).a0;
	if (rounds == 2)
		tmp = (*iters).b0;
	if (rounds == 3)
		tmp = (*iters).c0;
	if (rounds == 4)
		tmp = (*iters).d0;
	(*iters).j = 31;
	while ((*iters).i < count)
	{
		bits[(*iters).i] = (1 << (*iters).j) & tmp;
		(*iters).j--;
		(*iters).i++;
	}
	tmp <<= count;
	(*iters).i = 0;
	(*iters).j = count - 1;
	while ((*iters).j >= 0)
	{
		if (bits[(*iters).i])
	    tmp |= (1 << (*iters).j);
	  else
	    tmp &= ~(1 << (*iters).j);
		(*iters).i++;
		(*iters).j--;
	}
	if (rounds == 1)
		(*iters).a0 = tmp;
	if (rounds == 2)
		(*iters).b0 = tmp;
	if (rounds == 3)
		(*iters).c0 = tmp;
	if (rounds == 4)
		(*iters).d0 = tmp;
		//printf("222%d\n", (*iters).a0);
}

void round1_func(t_args *params, t_addition *iters, int i, int iflast)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned int tmp;

	const unsigned int table[16] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821};
	const int s[16] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 };
	count.k = i * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0 && !iflast)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	//printf("PLAINTEXT%s\n", ((*params).md5_buf));
	//printf("FFF%lu\n", (((*iters).b0 & (*iters).c0) | (~(*iters).b0 & (*iters).d0)));

	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			(((*iters).b0 & (*iters).c0) | (~(*iters).b0 & (*iters).d0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 += (*iters).b0;
			//printf("1ROUND %lu\n", (*iters).a0);
		}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			(((*iters).a0 & (*iters).b0) | (~(*iters).a0 & (*iters).c0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 += (*iters).a0;
			//printf("1ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			(((*iters).d0 & (*iters).a0) | (~(*iters).d0 & (*iters).b0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 += (*iters).d0;
			//printf("1ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			(((*iters).c0 & (*iters).d0) | (~(*iters).c0 & (*iters).a0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 += (*iters).c0;
			//printf("1ROUND %lu\n", (*iters).b0);
	}
}

void round2_func(t_args *params, t_addition *iters, int i, int iflast)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned int tmp;
	const unsigned int table[16] = {0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a};
	const int s[16] = { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 };
	const int index[16] = {1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12};
	count.k = index[i] * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0 && !iflast)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			(((*iters).b0 & (*iters).d0) | ((*iters).c0 & ~(*iters).d0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 += (*iters).b0;
			//printf("2ROUND %lu\n", (*iters).a0);
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			(((*iters).a0 & (*iters).c0) | ((*iters).b0 & ~(*iters).c0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 += (*iters).a0;
			//printf("2ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			(((*iters).d0 & (*iters).b0) | ((*iters).a0 & ~(*iters).b0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 += (*iters).d0;
			//printf("2ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			(((*iters).c0 & (*iters).a0) | ((*iters).d0 & ~(*iters).a0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 += (*iters).c0;
			//printf("2ROUND %lu\n", (*iters).b0);
	}
}

void round3_func(t_args *params, t_addition *iters, int i, int iflast)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned int tmp;
	const unsigned int table[16] = {0xfffa3942, 0x8771f681,
	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
	0x1fa27cf8, 0xc4ac5665};
	const int s[16] = { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 };
	const int index[16] = {5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2};
	count.k = index[i] * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0 && !iflast)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			((*iters).b0 ^ (*iters).c0 ^ (*iters).d0) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 += (*iters).b0;
			//printf("3ROUND %lu\n", (*iters).a0);
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			((*iters).a0 ^ (*iters).b0 ^ (*iters).c0) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 += (*iters).a0;
			//printf("3ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			((*iters).d0 ^ (*iters).a0 ^ (*iters).b0) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 += (*iters).d0;
			//printf("3ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			((*iters).c0 ^ (*iters).d0 ^ (*iters).a0) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 += (*iters).c0;
			//printf("3ROUND %lu\n", (*iters).b0);
	}
}

void round4_func(t_args *params, t_addition *iters, int i, int iflast)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned int tmp;
	const unsigned int table[16] =  {0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	const int s[16] = { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	const int index[16] = {0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};
	count.k = index[i] * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0 && !iflast)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			((*iters).c0 ^ ((*iters).b0 | ~(*iters).d0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 += (*iters).b0;
			//printf("4ROUND %lu\n", (*iters).a0);
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			((*iters).b0 ^ ((*iters).a0 | ~(*iters).c0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 += (*iters).a0;
			//printf("4ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			((*iters).a0 ^ ((*iters).d0 | ~(*iters).b0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 += (*iters).d0;
			//printf("4ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			((*iters).d0 ^ ((*iters).c0 | ~(*iters).a0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 += (*iters).c0;
			//printf("4ROUND %lu\n", (*iters).b0);
	}
}

void start_md5(t_args *params, t_addition *iters, int iflast)
{
	int i;

	i = 0;
		clear_iterators(iters);
		(*iters).a1 = (*iters).a0;
		(*iters).b1 = (*iters).b0;
		(*iters).c1 = (*iters).c0;
		(*iters).d1 = (*iters).d0;
		i = 0;
		while(i < 16)
		{
			round1_func(params, iters, i, iflast);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round2_func(params, iters, i, iflast);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round3_func(params, iters, i, iflast);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round4_func(params, iters, i, iflast);
			i++;
		}
		(*iters).a0 += (*iters).a1;
		(*iters).b0 += (*iters).b1;
		(*iters).c0 += (*iters).c1;
		(*iters).d0 += (*iters).d1;

}
