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

void print_md5_result(t_addition *iters, t_args *params)
{
	if (find_symb((*params).flags, 's', FLAG_LEN) >= 0 && find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
		ft_printf("%s\n", (*params).md5_str);
	else if (find_symb((*params).flags, 's', FLAG_LEN) >= 0)
			ft_printf("MD5 (\"%s\") ", (*params).md5_str);
	ft_printf("%lx", (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080));
	ft_printf("%lx", (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080));
	ft_printf("%lx", (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080));
	ft_printf("%lx", (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080));
	if ((*params).ifd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0)
		ft_printf(" %s\n", (*params).filename);
	else
		ft_printf("%c", '\n');
}

void	make_short_blocks_md5(t_args *params, int ret, unsigned char *str, t_addition *iters)
{
	t_addition				count;

	clear_iterators(&count);
	while (count.i < ret)
	{
		count.j = 0;
		while (count.i < ret && count.j < 64)
			(*params).md5_buf[count.j++] = str[count.i++];
		//printf("%d\n", j);
		if (count.j < 64)
			add_padding_md5(params, 64, ret);
		if (ft_strcmp((*params).cipher, "md5") == 0)
			start_md5(params, iters);
		if (ft_strcmp((*params).cipher, "sha256") == 0)
			start_sha256(params, iters, 1);
		count.j = 0;
		while (count.j < 64)
			(*params).md5_buf[count.j++] = 0;
	}
	if (ft_strcmp((*params).cipher, "md5") == 0)
	{
		if (ret == 0 || ret % 64 == 0)
		{
			add_padding_md5(params, 64, 0);
			start_md5(params, iters);
		}
		print_md5_result(iters, params);
		init_md5_vectors(iters);
	}
	if (ft_strcmp((*params).cipher, "sha256") == 0)
	{
		if (ret == 0 || ret * 8 == 448)
		{
			add_padding_md5(params, 64, 0);
			start_sha256(params, iters, 0);
		}
		ft_printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
		(*iters).f0, (*iters).h0);
		init_sha256_vectors(iters);
	}
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
      if (argv[i][1] == 's' && argv[i + 1])
      {
        //printf("%s\n", argv[i + 1]);
        (*params).md5_str = (unsigned char *)argv[i + 1];
        i++;
      }
			else if (argv[i][1] == 's')
			{
				ft_printf("%s\n", "usage: md5 [-pqr] [-s string] [files ...]");
				return (1);
			}
      j++;
      i++;
    }
    else if (((*params).ifd = open(argv[i], O_RDONLY)) > 0)
		{
			(*params).filename = argv[i];
			break;
		}
		else
		{
			ft_printf("md5: %s: No such file or directory\n", argv[i]);
			return (1);
		}
			/*{
				while (i < argc)
 			 {
 				 ft_printf("md5: %s %s\n", argv[i], "No such file or directory");
 				 i++;
 			 }
			 break;
		 }*/
			/*printf("%s\n", argv[i]);
			printf("%d\n", (*params).ifd);*/

    //}
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
	(*params).ifd = 0;
  (*params).cipher = NULL;
  (*params).md5_str = NULL;
	(*params).filename = NULL;
  //(*params).md5_buf = NULL;
}

unsigned int sha256_cycle_shift(unsigned int nbr, int count)
{
	t_addition				iters;
	unsigned int tmp;
	int bits[32];
	//printf("111%d\n", (*iters).a0);
	clear_iterators(&iters);

		tmp = nbr;
	while (iters.i < count)
	{
		bits[iters.i] = (1 << iters.j) & tmp;
		iters.j++;
		iters.i++;
	}
	tmp >>= count;
	//tmp %= 4294967296;
	iters.i = 0;
	iters.j = 32 - count;
	while (iters.i < count)
	{
		if (bits[iters.i])
	    tmp |= (1 << iters.j);
	  else
	    tmp &= ~(1 << iters.j);
		iters.i++;
		iters.j++;
	}
	return (tmp);
		//printf("222%d\n", (*iters).a0);
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

void start_sha256(t_args *params, t_addition *iters, int iflast)
{
	t_addition				count;
	t_sha256				sha_add_vars;

	const unsigned int square[64] = {0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
   0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
   0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
   0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
   0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
   0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
   0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
   0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

   unsigned int words[64];
		clear_iterators(&count);


	while (count.i < 16)
	{
		if ((count.k == 60 && (*params).md5_buf[count.k] == 0 && !iflast))
		words[count.i] = (*params).bytes_read * 8;
		else
		words[count.i] = (((((*params).md5_buf[count.k++] << 24) & 4294967295) +
			(((*params).md5_buf[count.k++] << 16) & 16777215)
+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
//printf("%u\n", words[count.i]);
		count.i++;
	}

	while (count.i < 64)
	{
		sha_add_vars.s0 = sha256_cycle_shift(words[count.i-15], 7) ^ sha256_cycle_shift(words[count.i-15], 18)
		^ (words[count.i-15] >> 3);
sha_add_vars.s1 = sha256_cycle_shift(words[count.i-2], 17) ^ sha256_cycle_shift(words[count.i-2], 19) ^ (words[count.i-2] >> 10);
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
		sha_add_vars.eps0 = sha256_cycle_shift((*iters).a1, 2) ^ sha256_cycle_shift((*iters).a1, 13) ^ sha256_cycle_shift((*iters).a1, 22);
        sha_add_vars.ma = ((*iters).a1 & (*iters).b1) ^ ((*iters).a1 & (*iters).c1) ^ ((*iters).b1 & (*iters).c1);
        sha_add_vars.t2 = sha_add_vars.eps0 + sha_add_vars.ma;
        sha_add_vars.eps1 = sha256_cycle_shift((*iters).e1, 6) ^ sha256_cycle_shift((*iters).e1, 11) ^ sha256_cycle_shift((*iters).e1, 25);
        sha_add_vars.ch = ((*iters).e1 & (*iters).f1) ^ ((~(*iters).e1) & (*iters).g1);
        sha_add_vars.t1 = (*iters).h1 + sha_add_vars.eps1 + sha_add_vars.ch + square[count.i] + words[count.i];
				//ft_printf("MMM%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
				//(*iters).f1, (*iters).h1);
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
	if (ft_strcmp((*params).cipher, "md5") == 0)
	{
		(*params).md5_buf[count++] = 128;
   while (count < 56)
     (*params).md5_buf[count++] = 0;
 	if ((i * 8) <= 255)
   	(*params).md5_buf[count++] = i * 8;
 	else
 			(*params).md5_buf[count++] = 0;
   while (count < len)
     (*params).md5_buf[count++] = 0;
	}
	if (ft_strcmp((*params).cipher, "sha256") == 0)
	{
		if (count != 0)
		(*params).md5_buf[count++] = 128;
   while (count < 63)
     (*params).md5_buf[count++] = 0;
 	if ((i * 8) <= 255)
   	(*params).md5_buf[63] = i * 8;
 	else
 			(*params).md5_buf[63] = 0;
	}
  /*printf("%s\n", (*params).md5_buf);
  count = 0;
  while (count < len)
    printf("%d\n", (*params).md5_buf[count++]);*/
}

void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
{
	clear_iterators(iters);
	while (((*iters).k = read(fd, &params->md5_buf, len)) > 0)
	{
		(*params).bytes_read += (*iters).k;
		/*if (find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
			ft_printf("%s", (*params).md5_buf);
		else if (fd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) < 0)
			ft_printf("MD5 (%s) = ", (*params).filename);*/
		if ((*iters).k < len)
			add_padding_md5(params, len, (*params).bytes_read);
		if (ft_strcmp((*params).cipher, "md5") == 0)
			start_md5(params, iters);
		if (ft_strcmp((*params).cipher, "sha256") == 0)
		{
			if ((*iters).k == len)
				start_sha256(params, iters, 1);
			else
			start_sha256(params, iters, 0);
		}
	}
	if (ft_strcmp((*params).cipher, "md5") == 0)
	{
		if ((*iters).k == 0 && (*params).bytes_read % 64 == 0)
		{
			add_padding_md5(params, len, (*params).bytes_read);
			start_md5(params, iters);
		}
		print_md5_result(iters, params);
		init_md5_vectors(iters);
	}
	if (ft_strcmp((*params).cipher, "sha256") == 0)
	{
		if ((*iters).k == 0 && (*params).bytes_read * 8 == 448)
		{
			add_padding_md5(params, len, (*params).bytes_read);
			start_sha256(params, iters, 0);
		}
		ft_printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
		(*iters).f0, (*iters).h0);
		init_sha256_vectors(iters);
	}
}


void init_sha256_vectors (t_addition *iters)
{
	(*iters).a0 = 0x6A09E667;
	(*iters).b0 = 0xBB67AE85;
	(*iters).c0 = 0x3C6EF372;
	(*iters).d0 = 0xA54FF53A;
	(*iters).e0 = 0x510E527F;
	(*iters).f0 = 0x9B05688C;
	(*iters).g0 = 0x1F83D9AB;
	(*iters).h0 = 0x5BE0CD19;
	(*iters).a1 = 0;
	(*iters).b1 = 0;
	(*iters).c1 = 0;
	(*iters).d1 = 0;
	(*iters).e1 = 0;
	(*iters).f1 = 0;
	(*iters).g1 = 0;
	(*iters).h1 = 0;
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
	if (ft_strcmp(params.cipher, "md5") == 0)
		init_md5_vectors(&iters);
	if (ft_strcmp(params.cipher, "sha256") == 0)
		init_sha256_vectors(&iters);
	if ((ft_strcmp(params.cipher, "md5") == 0 || (ft_strcmp(params.cipher, "sha256") == 0)) && params.ifd > 1)
	{
		//printf("LETEST%s\n", "LETEST");
		md5_reading(params.ifd, &params, 64, &iters);
		/*print_md5_result(&iters, &params);
		init_md5_vectors(&iters);*/
	}
  if ((ft_strcmp(params.cipher, "md5") == 0 || (ft_strcmp(params.cipher, "sha256") == 0)) && find_symb(params.flags, 's', FLAG_LEN) < 0)
	{
		md5_reading(0, &params, 64, &iters);
		/*print_md5_result(&iters, &params);
		init_md5_vectors(&iters);*/
	}
	if ((ft_strcmp(params.cipher, "md5") == 0 || (ft_strcmp(params.cipher, "sha256") == 0)) && find_symb(params.flags, 's', FLAG_LEN) >= 0)
	{
		params.bytes_read = ft_strlen((char *)params.md5_str);
		//printf("LE%d\n", params.bytes_read);
		make_short_blocks_md5(&params, params.bytes_read, params.md5_str, &iters);
		/*print_md5_result(&iters, &params);
		init_md5_vectors(&iters);*/
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
  if (params.ifd > 1)
    close(params.ifd);
  /*if (params.ofd > 1)
    close(params.ofd);*/
}
