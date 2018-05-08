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
	int len;
	if (ft_strcmp((*params).cipher, "sha512") == 0 )
		len = 128;
	else
		len = 64;
	while (count.i < ret)
	{
		count.j = 0;
		while (count.i < ret && count.j < len)
			(*params).md5_buf[count.j++] = str[count.i++];
		//printf("%d\n", j);
		if (count.j < len)
			add_padding_md5(params, len, count.j);
		if (ft_strcmp((*params).cipher, "md5") == 0)
			start_md5(params, iters);
			if (ft_strcmp((*params).cipher, "sha256") == 0)
		{
			//printf("JJJ%d\n", (*iters).j);
				if (count.j > 55)
		      start_sha256(params, iters, 1);
		    else
		    start_sha256(params, iters, 0);
		}
		  //start_sha256(params, iters, 1);
		if (ft_strcmp((*params).cipher, "sha512") == 0)
			start_sha512(params, iters, 1);
		count.j = 0;
		while (count.j < len)
			(*params).md5_buf[count.j++] = 0;
	}
	if (ft_strcmp((*params).cipher, "md5") == 0)
	{
		if (ret == 0 || ret % len == 0)
		{
			add_padding_md5(params, len, 0);
			start_md5(params, iters);
		}
		print_md5_result(iters, params);
		init_md5_vectors(iters);
	}
	if (ft_strcmp((*params).cipher, "sha256") == 0)
	{
		/*if (ret * 8 == 448)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}*/
		if ((*params).bytes_read % 64 == 0 )
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}
		if ((*params).bytes_read % 64 > 55)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}
		/*if ((*params).bytes_read % 64 == 0 || (*params).bytes_read % 56 == 0)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}*/
		/*if ((*params).bytes_read % 64 > 55 || ((*params).bytes_read > 55 && (*params).bytes_read < 64))
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}*/
		/*if ((*params).bytes_read > 55 && (*params).bytes_read < 64)
		{
			add_padding_md5(params, len, (*params).bytes_read);
			start_sha256(params, iters, 0);
		}*/
		/*if (ret == 0)
		{
			add_padding_md5(params, len, ret);
			start_sha256(params, iters, 0);
		}
		else if (ret * 8 == 448)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}
		else if ((*params).bytes_read % 64 == 0)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}*/
		ft_printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
		(*iters).g0, (*iters).h0);
		init_sha256_vectors(iters);
	}
	//if ((*iters).k == 0 && (*params).bytes_read % 64 == 0)

	if (ft_strcmp((*params).cipher, "sha512") == 0)
	{
		if (ret == 0 || ret % len == 0)
		{
			add_padding_md5(params, len, 0);
			start_sha512(params, iters, 0);
		}
		printf("%llx%llx%llx%llx%llx%llx%llx%llx\n", (*iters).aa0, (*iters).bb0, (*iters).cc0, (*iters).dd0, (*iters).ee0, (*iters).ff0,
		(*iters).gg0, (*iters).hh0);
		init_sha256_vectors(iters);
	}
	/*count.j = 0;
	while (count.j < len)
		(*params).md5_buf[count.j++] = 0;*/
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
  if (ft_strcmp(argv[1], "md5") != 0 && ft_strcmp(argv[1], "sha256") != 0 && ft_strcmp(argv[1], "sha512") != 0)
  {
    ft_printf("ft_ssl: Error: %s is an invalid command.\n\n", argv[1]);
    ft_printf("%s\n", "Standard commands:\n\nMessage Digest commands:");
    ft_printf("%s\n", "md5\nsha256\n\nCipher commands:\n");
    return (0);
  }
  if ((ft_strcmp(argv[1], "md5") == 0) && (res = check_md5_and_sha256_flags(argc, argv, params)) > 0)
    return (0);
  else if ((ft_strcmp(argv[1], "sha256") == 0 || ft_strcmp(argv[1], "sha512") == 0)&& (res = check_md5_and_sha256_flags(argc, argv, params)) > 0)
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

unsigned long long sha512_cycle_shift(unsigned long long nbr, int count)
{
	t_addition				iters;
	unsigned long long tmp;
	unsigned long long bits[32];
	//printf("111%d\n", (*iters).a0);
	clear_iterators(&iters);
	tmp = nbr;
	nbr = (tmp >> count) | (tmp << (63 - count));
	return (nbr);
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

void round1_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);

	unsigned char tmp1[4];
	unsigned int tmp;

	const unsigned int table[16] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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

void round2_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned char tmp1[4];
	unsigned int tmp;
	const unsigned int table[16] = {0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
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

void round3_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned int tmp;
	unsigned char tmp1[4];
	const unsigned int table[16] = {0xfffa3942, 0x8771f681,
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

void round4_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned int tmp;
	unsigned char tmp1[4];
	const unsigned int table[16] =  {0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
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

void start_sha512(t_args *params, t_addition *iters, int iflast)
{
	t_addition				count;
	t_sha512_vars				add_vars;
	unsigned long tmp1;
	unsigned int tmp2;
	const unsigned long long square[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
		0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

   unsigned long long words[64];
		clear_iterators(&count);

	while (count.i < 16)
	{
		tmp1 = (((((*params).md5_buf[count.k++] << 24) & 4294967295) +
			(((*params).md5_buf[count.k++] << 16) & 16777215)
+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
	tmp2 =
(((((*params).md5_buf[count.k++] << 24) & 4294967295) +
	(((*params).md5_buf[count.k++] << 16) & 16777215)
+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
		words[count.i] = (tmp1 << 32) + tmp2;
		printf("%llu\n", words[count.i]);
		count.i++;
	}
	if ((*params).md5_buf[127] == 0)
	words[15] = (*params).bytes_read * 8;
	printf("%llu\n", words[15]);
	while (count.i < 80)
	{
		add_vars.s0 = sha512_cycle_shift(words[count.i-15], 1) ^ sha512_cycle_shift(words[count.i-15], 8)
		^ (words[count.i-15] >> 7);
add_vars.s1 = sha512_cycle_shift(words[count.i-2], 19) ^ sha512_cycle_shift(words[count.i-2], 61) ^ (words[count.i-2] >> 6);
		words[count.i] = words[count.i-16] + add_vars.s0 + words[count.i-7] + add_vars.s1;
		count.i++;
	}
	printf("%llu\n", words[15]);
	printf("START%llx %llx %llx %llx %llx %llx %llx %llx \n", (*iters).aa0, (*iters).bb0, (*iters).cc0, (*iters).dd0, (*iters).ee0,
	(*iters).ff0, (*iters).gg0, (*iters).hh0);
	(*iters).aa1 = (*iters).aa0;
	(*iters).bb1 = (*iters).bb0;
	(*iters).cc1 = (*iters).cc0;
	(*iters).dd1 = (*iters).dd0;
	(*iters).ee1 = (*iters).ee0;
	(*iters).ff1 = (*iters).ff0;
	(*iters).gg1 = (*iters).gg0;
	(*iters).hh1 = (*iters).hh0;
	printf("%llu\n", words[15]);
	ft_printf("START%llx %llx %llx %llx %llx %llx %llx %llx \n", (*iters).aa1, (*iters).bb1, (*iters).cc1, (*iters).dd1, (*iters).ee1,
	(*iters).ff1, (*iters).gg1, (*iters).hh1);

	count.i = 0;
	while (count.i < 64)
	{
		//ft_printf("FFF%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
		//(*iters).f1, (*iters).h1);
		add_vars.eps0 = sha512_cycle_shift((*iters).aa1, 28) ^ sha512_cycle_shift((*iters).aa1, 34) ^ sha512_cycle_shift((*iters).aa1, 39);
        add_vars.ma = ((*iters).aa1 & (*iters).bb1) ^ ((*iters).aa1 & (*iters).cc1) ^ ((*iters).bb1 & (*iters).cc1);
        add_vars.t2 = add_vars.eps0 + add_vars.ma;
        add_vars.eps1 = sha512_cycle_shift((*iters).ee1, 14) ^ sha512_cycle_shift((*iters).ee1, 18) ^ sha512_cycle_shift((*iters).ee1, 41);
        add_vars.ch = ((*iters).ee1 & (*iters).ff1) ^ ((~(*iters).ee1) & (*iters).gg1);
        add_vars.t1 = (*iters).hh1 + add_vars.eps1 + add_vars.ch + square[count.i] + words[count.i];
				//ft_printf("MMM%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
				//(*iters).f1, (*iters).h1);
		(*iters).hh1 = (*iters).gg1;
		(*iters).gg1 = (*iters).ff1;
		(*iters).ff1 = (*iters).e1;
		(*iters).ee1 = (*iters).dd1 + add_vars.t1;
		(*iters).dd1 = (*iters).cc1;
		(*iters).cc1 = (*iters).bb1;
		(*iters).bb1 = (*iters).aa1;
		(*iters).aa1 = add_vars.t1 + add_vars.t2;
		ft_printf("EEE %d %llx %llx %llx %llx %llx %llx %llx %llx \n", count.i, (*iters).aa1, (*iters).bb1, (*iters).cc1, (*iters).dd1, (*iters).ee1,
		(*iters).ff1, (*iters).gg1, (*iters).hh1);
		count.i++;
	}
		(*iters).aa0 += (*iters).aa1;
		(*iters).bb0 += (*iters).bb1;
		(*iters).cc0 += (*iters).cc1;
		(*iters).dd0 += (*iters).dd1;
		(*iters).ee0 += (*iters).ee1;
		(*iters).ff0 += (*iters).ff1;
		(*iters).gg0 += (*iters).gg1;
		(*iters).hh0 += (*iters).hh1;
		printf("%s\n", "TEST1");
		//printf("START %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
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
	{//printf("WWW %u\n", words[count.i]);
		if ((*params).md5_buf[63] == 0 && count.i == 15 && !iflast)
		words[count.i] = (*params).bytes_read * 8;
		/*if ((*params).md5_buf[57] == 0 && count.i == 15 && !iflast)
		words[count.i] = 0;*/
		else
		words[count.i] = (((((*params).md5_buf[count.k++] << 24) & 4294967295) +
			(((*params).md5_buf[count.k++] << 16) & 16777215)
+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
		//printf("WWW %u\n", words[count.i]);
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
		//printf("1%d\n", count);
		if (count != 0 || (count == 0 && ((*params).bytes_read % 64 == 0)) /*|| (count == 0 && ((*params).bytes_read % 56 == 0))*/)
		//if (count < 56)
		(*params).md5_buf[count++] = 128;
   while (count < len)
     (*params).md5_buf[count++] = 0;
if (count < 56)
{
	if (((*params).bytes_read * 8) <= 255)
   	(*params).md5_buf[63] = (*params).bytes_read * 8;
 	else
 			(*params).md5_buf[63] = 0;
}
}
	if (ft_strcmp((*params).cipher, "sha512") == 0)
	{
		if (count != 0 && (*params).bytes_read % 64 != 0)
		(*params).md5_buf[count++] = 128;
   while (count < 128)
     (*params).md5_buf[count++] = 0;
 	if ((i * 8) <= 255)
   	(*params).md5_buf[127] = i * 8;
 	else
 			(*params).md5_buf[127] = 0;
	}
  //printf("%s\n", (*params).md5_buf);
  /*count = 0;
  while (count < len)
    printf("%d\n", (*params).md5_buf[count++]);*/
}

void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
{
	clear_iterators(iters);
	while (((*iters).k = read(fd, &params->md5_buf, len)) > 0)
	{
		(*params).bytes_read += (*iters).k;
		//printf("DDD%d\n", (*iters).k);
		/*if ((*params).md5_buf[(*iters).k - 1] == '\n')
			{
				(*params).md5_buf[(*iters).k - 1] = 0;
				(*iters).k--;
				(*params).bytes_read--;
			}*/
		/*if (find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
			ft_printf("%s", (*params).md5_buf);
		else if (fd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) < 0)
			ft_printf("MD5 (%s) = ", (*params).filename);*/
		if ((*iters).k < len)
			add_padding_md5(params, len, (*iters).k);
		if (ft_strcmp((*params).cipher, "md5") == 0)
			start_md5(params, iters);
		if (ft_strcmp((*params).cipher, "sha256") == 0)
		{
			if ((*iters).k > 55)
				start_sha256(params, iters, 1);
			else
			start_sha256(params, iters, 0);
		}
		if (ft_strcmp((*params).cipher, "sha512") == 0)
		{
			if ((*iters).k == len)
				start_sha512(params, iters, 1);
			else
			start_sha512(params, iters, 0);
		}
	}
	if (ft_strcmp((*params).cipher, "md5") == 0)
	{
		if ((*iters).k == 0 && (*params).bytes_read % len == 0)
		{
			add_padding_md5(params, len, (*params).bytes_read);
			start_md5(params, iters);
		}
		print_md5_result(iters, params);
		init_md5_vectors(iters);
	}
	//if ((*iters).k == 0 && ((*params).bytes_read % 64 == 0 || ((*params).bytes_read * 8) % 64 == 0 ))

	if (ft_strcmp((*params).cipher, "sha256") == 0)
	{
		if ((*params).bytes_read % 64 == 0)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}
		if ((*params).bytes_read % 64 > 55)
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}
		/*if ((*params).bytes_read > 55 && (*params).bytes_read < 64)
		{
			add_padding_md5(params, len, (*params).bytes_read);
			start_sha256(params, iters, 0);
		}*/
		/*
		if (((*params).bytes_read * 8 == 448))
		{
			add_padding_md5(params, len, 0);
			start_sha256(params, iters, 0);
		}*/
		ft_printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
		(*iters).g0, (*iters).h0);
		init_sha256_vectors(iters);
	}
	if (ft_strcmp((*params).cipher, "sha512") == 0)
	{
		if ((*iters).k == 0 && (*params).bytes_read % len == 0)
		{
			add_padding_md5(params, len, (*params).bytes_read);
			start_sha512(params, iters, 0);
		}
		printf("%llx%llx%llx%llx%llx%llx%llx%llx\n", (*iters).aa0, (*iters).bb0, (*iters).cc0, (*iters).dd0, (*iters).ee0, (*iters).ff0,
		(*iters).gg0, (*iters).hh0);
		init_sha512_vectors(iters);
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

void init_sha512_vectors (t_addition *iters)
{
	(*iters).aa0 = 0x6a09e667f3bcc908;
	(*iters).bb0 = 0xbb67ae8584caa73b;
	(*iters).cc0 = 0xbb67ae8584caa73b;
	(*iters).dd0 = 0xa54ff53a5f1d36f1;
	(*iters).ee0 = 0x510e527fade682d1;
	(*iters).ff0 = 0x9b05688c2b3e6c1f;
	(*iters).gg0 = 0x1f83d9abfb41bd6b;
	(*iters).hh0 = 0x5be0cd19137e2179;
	(*iters).aa1 = 0;
	(*iters).bb1 = 0;
	(*iters).cc1 = 0;
	(*iters).dd1 = 0;
	(*iters).ee1 = 0;
	(*iters).ff1 = 0;
	(*iters).gg1 = 0;
	(*iters).hh1 = 0;
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
	if (ft_strcmp(params.cipher, "sha512") == 0)
		init_sha512_vectors(&iters);
	if ((ft_strcmp(params.cipher, "md5") == 0 || ft_strcmp(params.cipher, "sha256") == 0 || ft_strcmp(params.cipher, "sha512") == 0) && params.ifd > 1)
	{
		//printf("LETEST%s\n", "LETEST");
		if (ft_strcmp(params.cipher, "sha512") == 0)
			md5_reading(params.ifd, &params, 128, &iters);
		else
			md5_reading(params.ifd, &params, 64, &iters);
		/*print_md5_result(&iters, &params);
		init_md5_vectors(&iters);*/
	}
  if ((ft_strcmp(params.cipher, "md5") == 0 || ft_strcmp(params.cipher, "sha256") == 0 || ft_strcmp(params.cipher, "sha512") == 0) && find_symb(params.flags, 's', FLAG_LEN) < 0)
	{
		if (ft_strcmp(params.cipher, "sha512") == 0)
		md5_reading(0, &params, 128, &iters);
		else
		md5_reading(0, &params, 64, &iters);
		/*print_md5_result(&iters, &params);
		init_md5_vectors(&iters);*/
	}
	if (((ft_strcmp(params.cipher, "md5") == 0 || ft_strcmp(params.cipher, "sha256") == 0 || ft_strcmp(params.cipher, "sha512") == 0)) && find_symb(params.flags, 's', FLAG_LEN) >= 0)
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
		return (0);
}
