/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:47:06 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/21 13:47:10 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

void	make_short_blocks_md5(t_args *params, int ret, unsigned char *str, t_addition *iters)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
		ft_printf("%s\n", str);
	while (i < ret)
	{
		j = 0;
		while (i < ret && j < 64)
			(*params).md5_buf[j++] = str[i++];
		//printf("%d\n", j);
		if (j < 64)
			add_padding_md5(params, 64, ret);
		start_md5(params, iters);
		j = 0;
		while (j < 64)
			(*params).md5_buf[j++] = 0;
	}
	if (ret == 0 || ret % 64 == 0)
	{
		add_padding_md5(params, 64, 0);
		start_md5(params, iters);
	}
	ft_printf("%lx", (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080));
	ft_printf("%lx", (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080));
	ft_printf("%lx", (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080));
	ft_printf("%lx\n", (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080));
}

void clear_iterators(t_addition *iters)
{
	int i;

	i = 0;
	(*iters).i = 0;
	(*iters).j = 0;
	(*iters).k = 0;
	(*iters).m = 0;
}

int		find_symb(char *str, char flag, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[i] == flag)
			return (i);
		i++;
	}
	return (-1);
}

void flags_normalize(char *all_flags, t_args *params, int len)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (i < len)
  {
    j = 0;
    while ((*params).flags[j] && (*params).flags[j] != all_flags[i])
      j++;
    if ((*params).flags[j] != all_flags[i])
      (*params).flags[j] = all_flags[i];
    i++;
  }
}

int check_md5_and_sha256_flags(int argc, char **argv, t_args *params)
{
  int i;
  int j;
  char *all_flags;

  j = 0;
  i = 2;
  if (!(all_flags = (char *)malloc(argc - 1)))
		return (1);
  all_flags[argc - 1] = 0;
  while (i < argc)
  {
    if (ft_strcmp(argv[i], "-p") == 0 || ft_strcmp(argv[i], "-q") == 0 ||
    ft_strcmp(argv[i], "-r") == 0 || ft_strcmp(argv[i], "-s") == 0)
    {
      all_flags[j] = argv[i][1];
      if (argv[i][1] == 's')
      {
        //printf("%s\n", argv[i + 1]);
        (*params).md5_str = (unsigned char *)argv[i + 1];
        i++;
      }
      j++;
      i++;
    }
    else
    {
      ft_printf("%s: invalid option -- %c\n", (*params).cipher, argv[i][1]);
      return (1);
    }
  }
  flags_normalize(all_flags, params, argc - 1);
  //printf("DDD%d\n", find_flag(params, 'i'));
  //printf("DDD%s\n", (*params).flags);
  //printf("DDD%d\n", (*params).ifd);
  /*if ((find_symb((*params).flags, 'i', FLAG_LEN)) >= 0 && (*params).ifd < 0)
  {
    ft_printf("%s\n", "base64: option requires an argument -- i");
    return (1);
  }*/
  return (0);
}

int if_valid_args(int argc, char **argv, t_args *params)
{
  int res;

  res = 0;
  if (argc == 1)
  {
    ft_printf("%s\n", "usage: ft_ssl command [command opts] [command args]");
    return (0);
  }
  if (ft_strcmp(argv[1], "md5") != 0 && ft_strcmp(argv[1], "sha256") != 0)
  {
    ft_printf("ft_ssl: Error: %s is an invalid command.\n\n", argv[1]);
    ft_printf("%s\n", "Standard commands:\n\nMessage Digest commands:");
    ft_printf("%s\n", "md5\nsha256\n\nCipher commands:\n");
    return (0);
  }
  if ((ft_strcmp(argv[1], "md5") == 0) && (res = check_md5_and_sha256_flags(argc, argv, params)) > 0)
    return (0);
  else if ((ft_strcmp(argv[1], "sha256") == 0)&& (res = check_md5_and_sha256_flags(argc, argv, params)) > 0)
    return (0);
  (*params).cipher = argv[1];
  return (1);
}

void clear_struct(t_args *params)
{
  int i;

  i = 0;
	(*params).bytes_read = 0;
  (*params).cipher = NULL;
  (*params).md5_str = NULL;
	(*params).md5_length = 0;
  //(*params).md5_buf = NULL;
}

void md5_cycle_shift(t_addition *iters, int count, int rounds)
{
	unsigned long tmp;
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
	tmp %= 4294967296;
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

void round1_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);

	unsigned char tmp1[4];
	unsigned long tmp;

	const unsigned long table[16] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821};
	const int s[16] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 };
	count.k = i * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	//printf("PLAINTEXT%lu\n", tmp);
	//printf("FFF%lu\n", (((*iters).b0 & (*iters).c0) | (~(*iters).b0 & (*iters).d0)));

	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			(((*iters).b0 & (*iters).c0) | (~(*iters).b0 & (*iters).d0)) + tmp + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 += (*iters).b0;
			(*iters).a0 %= 4294967296;
			//printf("1ROUND %lu\n", (*iters).a0);
		}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			(((*iters).a0 & (*iters).b0) | (~(*iters).a0 & (*iters).c0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 = ((*iters).d0 + (*iters).a0) % 4294967296;
			//printf("1ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			(((*iters).d0 & (*iters).a0) | (~(*iters).d0 & (*iters).b0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 = ((*iters).c0 + (*iters).d0) % 4294967296;
			//printf("1ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			(((*iters).c0 & (*iters).d0) | (~(*iters).c0 & (*iters).a0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 = ((*iters).b0 + (*iters).c0) % 4294967296;
			//printf("1ROUND %lu\n", (*iters).b0);
	}
}

void round2_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned char tmp1[4];
	unsigned long tmp;
	const unsigned long table[16] = {0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a};
	const int s[16] = { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 };
	const int index[16] = {1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12};
	count.k = index[i] * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	/*while (count.j < 4)
	{
		tmp1[count.j] = (*params).md5_buf[count.k];
		count.k++;
		count.j++;
	}
	clear_iterators(&count);
	count.m = 31;
	count.k = 3;
	while (count.m >= 0)
	{
		count.j = 7;
		while (count.j >= 0)
		{
				if ((1 << count.j) & tmp1[count.k])
					tmp |= (1 << count.m);
				else
					tmp &= ~(1 << count.m);
			count.m--;
			count.j--;
		}
		count.k--;
	}*/
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			(((*iters).b0 & (*iters).d0) | ((*iters).c0 & ~(*iters).d0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 = ((*iters).a0 + (*iters).b0) % 4294967296;
			//printf("2ROUND %lu\n", (*iters).a0);
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			(((*iters).a0 & (*iters).c0) | ((*iters).b0 & ~(*iters).c0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 = ((*iters).d0 + (*iters).a0) % 4294967296;
			//printf("2ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			(((*iters).d0 & (*iters).b0) | ((*iters).a0 & ~(*iters).b0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 = ((*iters).c0 + (*iters).d0) % 4294967296;
			//printf("2ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			(((*iters).c0 & (*iters).a0) | ((*iters).d0 & ~(*iters).a0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 = ((*iters).b0 + (*iters).c0) % 4294967296;
			//printf("2ROUND %lu\n", (*iters).b0);
	}
}

void round3_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned long tmp;
	unsigned char tmp1[4];
	const unsigned long table[16] = {0xfffa3942, 0x8771f681,
	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
	0x1fa27cf8, 0xc4ac5665};
	const int s[16] = { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 };
	const int index[16] = {5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2};
	count.k = index[i] * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	/*while (count.j < 4)
	{
		tmp1[count.j] = (*params).md5_buf[count.k];
		count.k++;
		count.j++;
	}
	clear_iterators(&count);
	count.m = 31;
	count.k = 3;
	while (count.m >= 0)
	{
		count.j = 7;
		while (count.j >= 0)
		{
				if ((1 << count.j) & tmp1[count.k])
					tmp |= (1 << count.m);
				else
					tmp &= ~(1 << count.m);
			count.m--;
			count.j--;
		}
		count.k--;
	}*/
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			((*iters).b0 ^ (*iters).c0 ^ (*iters).d0) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 = ((*iters).a0 + (*iters).b0) % 4294967296;
			//printf("3ROUND %lu\n", (*iters).a0);
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			((*iters).a0 ^ (*iters).b0 ^ (*iters).c0) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 = ((*iters).d0 + (*iters).a0) % 4294967296;
			//printf("3ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			((*iters).d0 ^ (*iters).a0 ^ (*iters).b0) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 = ((*iters).c0 + (*iters).d0) % 4294967296;
			//printf("3ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			((*iters).c0 ^ (*iters).d0 ^ (*iters).a0) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 = ((*iters).b0 + (*iters).c0) % 4294967296;
			//printf("3ROUND %lu\n", (*iters).b0);
	}
}

void round4_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned long tmp;
	unsigned char tmp1[4];
	const unsigned long table[16] =  {0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	const int s[16] = { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	const int index[16] = {0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};
	count.k = index[i] * 4 + 3;
	if (count.k == 59 && (*params).md5_buf[56] == 0)
	tmp = (*params).bytes_read * 8;
	else
	tmp = (((((*params).md5_buf[count.k--] << 24) & 4294967295) + (((*params).md5_buf[count.k--] << 16) & 16777215)
+ (((*params).md5_buf[count.k--] << 8) & 65535) + ((*params).md5_buf[count.k] & 255)));
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
			(*iters).a0 = ((*iters).a0 +
			((*iters).c0 ^ ((*iters).b0 | ~(*iters).d0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 1);
			(*iters).a0 = ((*iters).a0 + (*iters).b0) % 4294967296;
			//printf("4ROUND %lu\n", (*iters).a0);
	}
	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
			(*iters).d0 = ((*iters).d0 +
			((*iters).b0 ^ ((*iters).a0 | ~(*iters).c0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 4);
			(*iters).d0 = ((*iters).d0 + (*iters).a0) % 4294967296;
			//printf("4ROUND %lu\n", (*iters).d0);
	}
	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
			(*iters).c0 = ((*iters).c0 +
			((*iters).a0 ^ ((*iters).d0 | ~(*iters).b0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 3);
			(*iters).c0 = ((*iters).c0 + (*iters).d0) % 4294967296;
			//printf("4ROUND %lu\n", (*iters).c0);
	}
	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
			(*iters).b0 = ((*iters).b0 +
			((*iters).d0 ^ ((*iters).c0 | ~(*iters).a0)) + tmp + table[i]) % 4294967296;
			md5_cycle_shift(iters, s[i], 2);
			(*iters).b0 = ((*iters).b0 + (*iters).c0) % 4294967296;
			//printf("4ROUND %lu\n", (*iters).b0);
	}
}

void start_md5(t_args *params, t_addition *iters)
{
	int i;

	i = 0;
		clear_iterators(iters);
		(*iters).a1 = (*iters).a0;
		(*iters).b1 = (*iters).b0;
		(*iters).c1 = (*iters).c0;
		(*iters).d1 = (*iters).d0;
		//printf("START %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
		i = 0;
		while(i < 16)
		{
			round1_func(params, iters, i);
			//printf("1ROUND %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round2_func(params, iters, i);
			//printf("2ROUND %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round3_func(params, iters, i);
			//printf("3ROUND %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round4_func(params, iters, i);
			//printf("4ROUND %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
			i++;
		}
		(*iters).a0 = ((*iters).a0 + (*iters).a1) % 4294967296;
		(*iters).b0 = ((*iters).b0 + (*iters).b1) % 4294967296;
		(*iters).c0 = ((*iters).c0 + (*iters).c1) % 4294967296;
		(*iters).d0 = ((*iters).d0 + (*iters).d1) % 4294967296;
		/*(*iters).a0 = (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080);
		(*iters).b0 = (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080);
		(*iters).c0 = (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080);
		(*iters).d0 = (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080);*/
		//printf("END %lu %lu %lu %lu \n", (*iters).d0, (*iters).c0, (*iters).b0, (*iters).a0);
		//ft_printf("%x %x %x %x \n", (*iters).d0, (*iters).c0, (*iters).b0, (*iters).a0);
		//ft_printf("%x %x %x %x \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
		/*ft_printf("%lx", (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080));
		ft_printf("%lx", (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080));
		ft_printf("%lx", (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080));
		ft_printf("%lx\n", (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080));*/
}

void add_padding_md5(t_args *params, int len, int count)
{
	int i;

	i = count;
	 (*params).md5_buf[count++] = 128;
  while (count < 56)
    (*params).md5_buf[count++] = 0;

	if ((i * 8) <= 255)
  	(*params).md5_buf[count++] = i * 8;
	else
		{
			(*params).md5_buf[count++] = 0;
			(*params).md5_length = i * 8;
		}
  while (count < len)
    (*params).md5_buf[count++] = 0;
  /*printf("%s\n", (*params).md5_buf);
  count = 0;
  while (count < len)
    printf("%d\n", (*params).md5_buf[count++]);*/
}

void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
{
	clear_iterators(iters);
	while (((*iters).k = read(0, &params->md5_buf, len)) > 0)
	{
		(*params).bytes_read += (*iters).k;
		if ((*iters).k < len)
			add_padding_md5(params, len, (*params).bytes_read);
		start_md5(params, iters);
	}
	if ((*iters).k == 0 && (*params).bytes_read % 64 == 0)
	{
		add_padding_md5(params, len, (*params).bytes_read);
		start_md5(params, iters);
	}
	ft_printf("%lx", (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080));
	ft_printf("%lx", (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080));
	ft_printf("%lx", (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080));
	ft_printf("%lx\n", (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080));
}

void init_md5_vectors (t_addition *iters)
{
	(*iters).a0 = 0x67452301;
	(*iters).b0 = 0xEFCDAB89;
	(*iters).c0 = 0x98BADCFE;
	(*iters).d0 = 0x10325476;
	(*iters).a1 = 0;
	(*iters).b1 = 0;
	(*iters).c1 = 0;
	(*iters).d1 = 0;
}

int main (int argc, char **argv)
{
  t_addition				iters;

	clear_iterators(&iters);
  t_args params;

  clear_struct(&params);
  if (!if_valid_args(argc, argv, &params))
    return (0);
	init_md5_vectors(&iters);
  if (ft_strcmp(params.cipher, "md5") == 0 && find_symb(params.flags, 's', FLAG_LEN) < 0)
    md5_reading(0, &params, 64, &iters);
	else if (ft_strcmp(params.cipher, "md5") == 0 && find_symb(params.flags, 's', FLAG_LEN) >= 0)
	{
		params.bytes_read = ft_strlen((char *)params.md5_str);
		//printf("LE%d\n", params.bytes_read);
		make_short_blocks_md5(&params, params.bytes_read, params.md5_str, &iters);
	}

  /*else if (((ft_strcmp(params.cipher, "des") == 0) || (ft_strcmp(params.cipher, "des-ecb") == 0)
|| (ft_strcmp(params.cipher, "des-cbc") == 0)) && (find_symb(params.flags, 'd', FLAG_LEN) < 0)
&& (find_symb(params.flags, 'i', FLAG_LEN)) < 0)
    des_reading(0, &params, 48);
    else if (((ft_strcmp(params.cipher, "des") == 0) || (ft_strcmp(params.cipher, "des-ecb") == 0)
  || (ft_strcmp(params.cipher, "des-cbc") == 0)) && (find_symb(params.flags, 'd', FLAG_LEN) < 0)
&& (find_symb(params.flags, 'i', FLAG_LEN)) >= 0)
    des_reading(params.ifd, &params, 48);
  else if (((ft_strcmp(params.cipher, "des") == 0) || (ft_strcmp(params.cipher, "des-ecb") == 0)
|| (ft_strcmp(params.cipher, "des-cbc") == 0)) && (find_symb(params.flags, 'd', FLAG_LEN) >= 0)
&& (find_symb(params.flags, 'i', FLAG_LEN)) < 0)
    des_reading(0, &params, 64);
    else if (((ft_strcmp(params.cipher, "des") == 0) || (ft_strcmp(params.cipher, "des-ecb") == 0)
  || (ft_strcmp(params.cipher, "des-cbc") == 0)) && (find_symb(params.flags, 'd', FLAG_LEN) >= 0)
&& (find_symb(params.flags, 'i', FLAG_LEN)) >= 0)
    des_reading(params.ifd, &params, 64);*/
  /*if (params.ifd > 1)
    close(params.ifd);
  if (params.ofd > 1)
    close(params.ofd);*/
}
