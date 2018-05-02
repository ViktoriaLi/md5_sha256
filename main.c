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
	while (i < ret)
	{
		j = 0;
		while (i < ret && j < 64)
		{
			(*params).md5_buf[j++] = str[i++];
		}
		//printf("%d\n", j);
		if (j < 64)
			add_padding_md5(params, 64, j);
		start_md5(params, iters);
		j = 0;
		while (j < 64)
			(*params).md5_buf[j++] = 0;
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
  //(*params).md5_buf = NULL;
}

/*int f_func(unsigned char *str1, unsigned char *str2, unsigned char *str3)
{
	int i;
	unsigned char tmp[4];

	i = 0;
	while (i < 4)
	{
		tmp[i] = ((*iters).str1[i] & (*iters).str2[i]) | (!(*iters).str1[i] & (*iters).str3[i]);
		i++;
	}
	return (tmp);
}

int g_func(unsigned char *str1, unsigned char *str2, unsigned char *str3)
{
	int i;
	unsigned char tmp[4];

	i = 0;
	while (i < 4)
	{
		tmp[i] = ((*iters).str1[i] & (*iters).str3[i]) | ((*iters).str2[i] & !(*iters).str3[i]);
		i++;
	}
	return (tmp);
}

int h_func(unsigned char *str1, unsigned char *str2, unsigned char *str3)
{
	int i;
	unsigned char tmp[4];

	i = 0;
	while (i < 4)
	{
		tmp[i] = (*iters).str1[i] ^ (*iters).str2[i] ^ (*iters).str3[i];
		i++;
	}
	return (tmp);
}

int i_func(unsigned char *str1, unsigned char *str2, unsigned char *str3)
{
	int i;
	unsigned char tmp[4];

	i = 0;
	while (i < 4)
	{
		tmp[i] = (*iters).str2 ^ ((*iters).str1 | !(*iters).str3);
		i++;
	}
	return (tmp);
}*/

void md5_cycle_shift(t_addition *iters, int count, int rounds)
{
	t_addition				iters;

	clear_iterators(&iters);

	unsigned char res[4];
	unsigned char *tmp;
	unsigned char *dest;
	int bits[32];

	if (rounds == 1)
		tmp = (*iters).str1;
	if (rounds == 2)
		tmp = (*iters).str2;
	if (rounds == 3)
		tmp = (*iters).str3;
	if (rounds == 4)
		tmp = (*iters).str4;
	while (iters.i < count)
	{
		iters.j = 7;
		while (iters.j >= 0 && iters.i < count)
		{
			bits[iters.i] = (1 << iters.j) & key_56[iters.k];
			iters.j--;
			iters.i++;
		}
		iters.k++;
	}
	clear_iterators(&iters);
	iters.m = count / 8;
	iters.k = iters.m;
	while (iters.i < 4)
	{
		while (iters.m < 4)
		{
			dest[iters.i] = tmp[iters.m]
			iters.i++;
		}
		iters.m = iters.m;
		while (iters.m < iters.k)
		{
			dest[iters.i] = tmp[iters.m]
			iters.i++;
		}
	}
}

void round1_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);

	unsigned char tmp[4];
	const long long table[16] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821};
	const int s[16] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 };
	count.k = i * 4;
	while (count.j < 4)
	{
		tmp[count.j] = (*params).md5_buf[count.k];
		count.k++;
		count.j++;
	}
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		while (count.m < 4)
		{
			(*iters).str1[count.m] = ((*iters).str1[count.m] +
			((*iters).str1[count.m] & (*iters).str2[count.m]) | ((!(*iters).str1[count.m]) & (*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).str1[count.m] += (*iters).str2[count.m];
			count.m++;
		}
	}

	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		while (count.m < 4)
		{
			(*iters).str4[count.m] = ((*iters).str4[count.m] +
			((*iters).str1[count.m] & (*iters).str2[count.m]) | ((!(*iters).str1[count.m]) & (*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).str4[count.m] += (*iters).str1[count.m];
			count.m++;
		}
	}

	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		while (count.m < 4)
		{
			(*iters).str3[count.m] =((*iters).str3[count.m] +
			((*iters).str1[count.m] & (*iters).str2[count.m]) | ((!(*iters).str1[count.m]) & (*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).str3[count.m] += (*iters).str4[count.m];
			count.m++;
		}
	}

	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		while (count.m < 4)
		{
			(*iters).str2[count.m] = ((*iters).str2[count.m] +
			((*iters).str1[count.m] & (*iters).str2[count.m]) | ((!(*iters).str1[count.m]) & (*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).str2[count.m] = (*iters).str3[count.m];
			count.m++;
		}
	}
}

void round2_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned char tmp[4];
	const long long table[16] = {0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
	0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a};
	const int s[16] = { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 };
	const int index[16] = {1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12};
	count.k = index[i] * 4;
	while (count.j < 4)
	{
		tmp[count.j] = (*params).md5_buf[count.k];
		count.k++;
		count.j++;
	}
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		while (count.m < 4)
		{
			(*iters).str1[count.m] = ((*iters).str1[count.m] +
			((*iters).str1[count.m] & (*iters).str3[count.m]) | ((*iters).str2[count.m] & !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).str1[count.m] += (*iters).str2[count.m];
			count.m++;
		}
	}

	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		while (count.m < 4)
		{
			(*iters).str4[count.m] = ((*iters).str4[count.m] +
			((*iters).str1[count.m] & (*iters).str3[count.m]) | ((*iters).str2[count.m] & !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).str4[count.m] += (*iters).str1[count.m];
			count.m++;
		}
	}

	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		while (count.m < 4)
		{
			(*iters).str3[count.m] =((*iters).str3[count.m] +
			((*iters).str1[count.m] & (*iters).str3[count.m]) | ((*iters).str2[count.m] & !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).str3[count.m] += (*iters).str4[count.m];
			count.m++;
		}
	}

	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		while (count.m < 4)
		{
			(*iters).str2[count.m] = ((*iters).str2[count.m] +
			((*iters).str1[count.m] & (*iters).str3[count.m]) | ((*iters).str2[count.m] & !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).str2[count.m] = (*iters).str3[count.m];
			count.m++;
		}
	}
}

void round3_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned char tmp[4];
	const long long table[16] = {0xfffa3942, 0x8771f681,
	0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
	0x1fa27cf8, 0xc4ac5665};
	const int s[16] = { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 };
	const int index[16] = {5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2};
	count.k = index[i] * 4;
	while (count.j < 4)
	{
		tmp[count.j] = (*params).md5_buf[count.k];
		count.k++;
		count.j++;
	}
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		while (count.m < 4)
		{
			(*iters).str1[count.m] = ((*iters).str1[count.m] +
			(*iters).str1[count.m] ^ (*iters).str2[count.m] ^ (*iters).str3[count.m]
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).str1[count.m] += (*iters).str2[count.m];
			count.m++;
		}
	}

	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		while (count.m < 4)
		{
			(*iters).str4[count.m] = ((*iters).str4[count.m] +
			(*iters).str1[count.m] ^ (*iters).str2[count.m] ^ (*iters).str3[count.m]
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).str4[count.m] += (*iters).str1[count.m];
			count.m++;
		}
	}

	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		while (count.m < 4)
		{
			(*iters).str3[count.m] =((*iters).str3[count.m] +
			(*iters).str1[count.m] ^ (*iters).str2[count.m] ^ (*iters).str3[count.m]
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).str3[count.m] += (*iters).str4[count.m];
			count.m++;
		}
	}

	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		while (count.m < 4)
		{
			(*iters).str2[count.m] = ((*iters).str2[count.m] +
			(*iters).str1[count.m] ^ (*iters).str2[count.m] ^ (*iters).str3[count.m]
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).str2[count.m] = (*iters).str3[count.m];
			count.m++;
		}
	}
}

void round4_func(t_args *params, t_addition *iters, int i)
{
	t_addition				count;

	clear_iterators(&count);
	unsigned char tmp[4];
	const long long table[16] =  {0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
	0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	const int s[16] = { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	const int index[16] = {0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};
	count.k = index[i] * 4;
	while (count.j < 4)
	{
		tmp[count.j] = (*params).md5_buf[count.k];
		count.k++;
		count.j++;
	}
	if (i == 0 || i == 4 || i == 8 || i == 12)
	{
		while (count.m < 4)
		{
			(*iters).str1[count.m] = ((*iters).str1[count.m] +
			(*iters).str2[count.m] ^ ((*iters).str1[count.m] | !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 1);
			(*iters).str1[count.m] += (*iters).str2[count.m];
			count.m++;
		}
	}

	else if (i == 1 || i == 5 || i == 9 || i == 13)
	{
		while (count.m < 4)
		{
			(*iters).str4[count.m] = ((*iters).str4[count.m] +
			(*iters).str2[count.m] ^ ((*iters).str1[count.m] | !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 4);
			(*iters).str4[count.m] += (*iters).str1[count.m];
			count.m++;
		}
	}

	else if (i == 2 || i == 6 || i == 10 || i == 14)
	{
		while (count.m < 4)
		{
			(*iters).str3[count.m] =((*iters).str3[count.m] +
			(*iters).str2[count.m] ^ ((*iters).str1[count.m] | !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 3);
			(*iters).str3[count.m] += (*iters).str4[count.m];
			count.m++;
		}
	}

	else if (i == 3 || i == 7 || i == 11 || i == 15)
	{
		while (count.m < 4)
		{
			(*iters).str2[count.m] = ((*iters).str2[count.m] +
			(*iters).str2[count.m] ^ ((*iters).str1[count.m] | !(*iters).str3[count.m])
			+ tmp[count.m] + table[i]);
			md5_cycle_shift(iters, s[i], 2);
			(*iters).str2[count.m] = (*iters).str3[count.m];
			count.m++;
		}
	}
}

void start_md5(t_args *params, t_addition *iters)
{
	int i;

	i = 0;
		clear_iterators(iters);
		while (i < 4)
		{
			(*iters).str_a[i] = (*iters).str1[i];
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str_b[i] = (*iters).str2[i];
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str_c[i] = (*iters).str3[i];
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str_d[i] = (*iters).str4[i];
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round1_func(params, iters, i);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round2_func(params, iters, i);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round3_func(params, iters, i);
			i++;
		}
		i = 0;
		while(i < 16)
		{
			round4_func(params, iters, i);
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str1[i] += (*iters).str_a[i];
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str2[i] += (*iters).str_b[i];
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str3[i] += (*iters).str_c[i];
			i++;
		}
		i = 0;
		while (i < 4)
		{
			(*iters).str4[i] += (*iters).str_d[i];
			i++;
		}
		printf("%s %s %s %s \n", (*iters).str1, (*iters).str2, (*iters).str3, (*iters).str4);
		i = 0;
				printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n", (*iters).str1[0], (*iters).str1[1], (*iters).str1[2],
		(*iters).str1[3], (*iters).str2[0], (*iters).str2[1], (*iters).str2[2], (*iters).str2[3], (*iters).str3[0],
	(*iters).str3[1], (*iters).str3[2], (*iters).str3[3], (*iters).str4[0], (*iters).str4[1], (*iters).str4[2],
(*iters).str4[3]);
}

void add_padding_md5(t_args *params, int len, int count)
{
	int i;

	i = count;
	 (*params).md5_buf[count++] = 128;
  while (count < 56)
    (*params).md5_buf[count++] = 0;
  (*params).md5_buf[count++] = i * 8;
  while (count < len)
    (*params).md5_buf[count++] = 0;
  printf("%s\n", (*params).md5_buf);
  count = 0;
  while (count < len)
    printf("%d\n", (*params).md5_buf[count++]);
}

void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
{
	clear_iterators(iters);
	while (((*iters).k = read(0, &params->md5_buf, len)) > 0)
	{
		if ((*params).md5_buf[(*iters).k - 1] == '\n')
		{
			(*params).md5_buf[(*iters).k - 1] = 0;
			(*iters).k--;
		}
		(*params).bytes_read += (*iters).k;
		if ((*iters).k < len)
			add_padding_md5(params, len, (*iters).k);
		start_md5(params, iters);
	}
}

void init_md5_vectors (t_addition *iters)
{
	(*iters).str1 = (unsigned char *)0x67452301;
	(*iters).str2 = (unsigned char *)0xEFCDAB89;
	(*iters).str3 = (unsigned char *)0x98BADCFE;
	(*iters).str4 = (unsigned char *)0x10325476;
	/*(*iters).str1[0] = 103;
	(*iters).str1[1] = 69;
	(*iters).str1[2] = 35;
	(*iters).str1[3] = 1;
	(*iters).str2[0] = 239;
	(*iters).str2[1] = 205;
	(*iters).str2[2] = 171;
	(*iters).str2[3] = 137;
	(*iters).str3[0] = 152;
	(*iters).str3[1] = 186;
	(*iters).str3[2] = 220;
	(*iters).str3[3] = 254;
	(*iters).str4[0] = 16;
	(*iters).str4[1] = 50;
	(*iters).str4[2] = 84;
	(*iters).str4[3] = 118;*/
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
		printf("LE%d\n", params.bytes_read);
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
