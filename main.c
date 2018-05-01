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

void clear_iterators(t_addition *iters)
{
	int i;

	i = 0;
	while (i < 4)
		(*iters).str1[i++] = 0;
	i = 0;
	while (i < 4)
		(*iters).str2[i++] = 0;
  i = 0;
  while (i < 4)
  	(*iters).str3[i++] = 0;
  i = 0;
  while (i < 4)
  	(*iters).str4[i++] = 0;
	(*iters).i = 0;
	(*iters).j = 0;
	(*iters).k = 0;
	(*iters).m = 0;
}

int get_line(t_args *params)
{
	int i;
	int ret;
	int k;
	unsigned char *buf;
	unsigned char *res;
	unsigned char *tmp;

	i = 0;
	k = 1;
	buf = ft_memalloc(64);
	ret = 1;
	while (ret > 0)
	{
		if (i == 64 * k)
		{
			k *= 2;
			tmp = ft_memalloc(64 * k);
			ft_memcpy(tmp, buf, i);
			free(buf);
			buf = tmp;
		}
		ret = read(0, &buf, 64);
		i += ret;
	}
	buf[i - 1] = 0;
	res = ft_memalloc(i);
	ft_memcpy(res, buf, i);
	(*params).md5_buf = res;
	//*len = i;
	free(buf);
	return (ret);
}


/*void	md5_reading(int fd, t_args *params, int len)
{
	t_addition				iters;

	clear_iterators(&iters);
	while ((iters.k = read(0, &params->md5_buf, len)) > 0)
	{
		make_short_blocks(params, iters.k, 64, (*params).md5_buf);
		iters.i = 0;
		while (iters.i < iters.k)
			(*params).md5_buf[iters.i++] = 0;
		if (iters.k == 64 && (find_symb((*params).flags, 'd', FLAG_LEN)) < 0
			&& (find_symb((*params).flags, 'o', FLAG_LEN)) >= 0)
			write((*params).ofd, "\n", 1);
		else if (iters.k == 64 &&
			(find_symb((*params).flags, 'd', FLAG_LEN)) < 0)
			write(1, "\n", 1);
	}
}*/

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
  //printf("%s\n", (*params).flags);
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
        (*params).md5_buf = (unsigned char *)argv[i + 1];
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

  (*params).cipher = NULL;
  (*params).md5_str = NULL;
  (*params).md5_buf = NULL;
}

int main (int argc, char **argv)
{
  t_addition				iters;

	clear_iterators(&iters);
  int len;
  int len_out;
  t_args params;

  clear_struct(&params);
  len = 0;
  len_out = 0;
  if (!if_valid_args(argc, argv, &params))
    return (0);
  if (ft_strcmp(params.cipher, "md5") == 0 && !params.md5_buf)
    len = get_line(&params);
  printf("%s\n", params.md5_buf);
  len = ft_strlen((char *)params.md5_buf);
  printf("%d\n", len);
  len_out = 64 * (len / 64 + 1);
  params.md5_str = (unsigned char *)malloc(sizeof(unsigned char) * len_out);
  params.md5_str[len_out] = 0;
  printf("%d\n", len_out);
  while (iters.i < len)
  {
    params.md5_str[iters.i] = params.md5_buf[iters.i];
    iters.i++;
  }
  params.md5_str[iters.i++] = 128;
  while (iters.i < len_out - 8)
    params.md5_str[iters.i++] = 0;
  params.md5_str[iters.i++] = len * 8;
  while (iters.i < len_out)
    params.md5_str[iters.i++] = 0;
  printf("%s\n", params.md5_str);
  iters.i = 0;
  while (iters.i < len_out)
    printf("%d\n", params.md5_str[iters.i++]);
  iters.str1[0] = 1;
  iters.str1[1] = 35;
  iters.str1[2] = 69;
  iters.str1[3] = 103;
  iters.str2[0] = 137;
  iters.str2[1] = 171;
  iters.str2[2] = 205;
  iters.str2[3] = 239;
  iters.str3[0] = 254;
  iters.str3[1] = 220;
  iters.str3[2] = 186;
  iters.str3[3] = 152;
  iters.str4[0] = 118;
  iters.str4[1] = 84;
  iters.str4[2] = 50;
  iters.str4[3] = 16;

  iters.i = 0;
  iters.str1[]
  while (iters.i < len_out)
  {
    while (iters.j < 16)

    iters.i += 64;
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
