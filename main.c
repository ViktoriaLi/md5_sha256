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

size_t    ft_strlen(const char *s)
{
  size_t i;

  i = 0;
  while (s[i] != 0)
    i++;
  return (i);
}


int   ft_strcmp(const char *s1, const char *s2)
{
  int i;

  i = 0;
  while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
    i++;
  if (s1[i] != s2[i])
    return (int)((unsigned char)s1[i] - (unsigned char)s2[i]);
  return (0);
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
			{md5:
        printf("%s: option requires an argument -- s\n", argv[1]);
				printf("%s\n", "usage: md5 [-pqr] [-s string] [files ...]");
				return (1);
			}
      j++;
      i++;
    }
    else if (((*params).ifd = open(argv[i], O_RDONLY)) > 0)
		{
			(*params).filename = argv[i];
      i++;
      j = 0;
      if (i < argc)
      {
        (*params).argvs = (char **)malloc(sizeof(char *) * (argc - i));
        j = 0;
        while (j < argc)
      		(*params).argvs[j++] = NULL;
          j = 0;
        while (i < argc)
        {
          (*params).argvs[j] = argv[i];
          //printf("%s\n", (*params).argvs[j]);
          i++;
          j++;
        }
        (*params).if_no_file = j;
        (*params).argvs[j] = NULL;
      }
			break;
		}
		else
			printf("md5: %s: No such file or directory\n", argv[i]);
  }
  flags_normalize(all_flags, params, argc - 1);
  return (0);
}

int if_valid_args(int argc, char **argv, t_args *params)
{
  int res;

  res = 0;
  if (argc == 1)
  {
    printf("%s\n", "usage: ft_ssl command [command opts] [command args]");
    return (0);
  }
  if (ft_strcmp(argv[1], "md5") != 0 && ft_strcmp(argv[1], "sha256") != 0 && ft_strcmp(argv[1], "sha512") != 0)
  {
    printf("ft_ssl: Error: %s is an invalid command.\n\n", argv[1]);
    printf("%s\n", "Standard commands:\n\nMessage Digest commands:");
    printf("%s\n", "md5\nsha256\n\nCipher commands:\n");
    return (0);
  }
  if ((ft_strcmp(argv[1], "md5") == 0) && (res = check_md5_and_sha256_flags(argc, argv, params)) > 0)
    return (0);
  else if ((ft_strcmp(argv[1], "sha256") == 0 || ft_strcmp(argv[1], "sha512") == 0)&& (res = check_md5_and_sha256_flags(argc, argv, params)) > 0)
    return (0);
  (*params).cipher = argv[1];
  return (1);
}



int main (int argc, char **argv)
{
  int i = 0;
  t_addition				iters;
	clear_iterators(&iters);
  t_args params;
  clear_struct(&params, argc);
  if (!if_valid_args(argc, argv, &params))
    return (0);
	if (ft_strcmp(params.cipher, "md5") == 0)
		init_md5_vectors(&iters);
	if (ft_strcmp(params.cipher, "sha256") == 0)
		init_sha256_vectors(&iters);
	if (ft_strcmp(params.cipher, "sha512") == 0)
		init_sha512_vectors(&iters);
  if (((ft_strcmp(params.cipher, "md5") == 0 || ft_strcmp(params.cipher, "sha256") == 0 || ft_strcmp(params.cipher, "sha512") == 0)))
{
  if  (find_symb(params.flags, 'p', FLAG_LEN) >= 0)
  {
    //printf("%s\n", "INPUT");
    i = 0;
    while (i < 128)
      params.md5_buf[i++] = 0;
    params.bytes_read = 0;
    if (ft_strcmp(params.cipher, "sha512") == 0)
    md5_reading(0, &params, 128, &iters);
    else
    md5_reading(0, &params, 64, &iters);
  }
  if (ft_strcmp(params.cipher, "md5") == 0)
    init_md5_vectors(&iters);
  if (ft_strcmp(params.cipher, "sha256") == 0)
    init_sha256_vectors(&iters);
  if (ft_strcmp(params.cipher, "sha512") == 0)
    init_sha512_vectors(&iters);
    i = 0;
    while (i < 128)
      params.md5_buf[i++] = 0;
    params.bytes_read = 0;
    if (find_symb(params.flags, 's', FLAG_LEN) >= 0)
    {
      params.bytes_read = ft_strlen((char *)params.md5_str);
      //printf("LE%d\n", params.bytes_read);
      make_short_blocks_md5(&params, params.bytes_read, params.md5_str, &iters);
    }

    if (ft_strcmp(params.cipher, "md5") == 0)
  		init_md5_vectors(&iters);
  	if (ft_strcmp(params.cipher, "sha256") == 0)
  		init_sha256_vectors(&iters);
  	if (ft_strcmp(params.cipher, "sha512") == 0)
  		init_sha512_vectors(&iters);
    i = 0;
    while (i < 128)
      params.md5_buf[i++] = 0;
    params.bytes_read = 0;
    if (params.ifd > 1)
    {
      if (ft_strcmp(params.cipher, "sha512") == 0)
        md5_reading(params.ifd, &params, 128, &iters);
      else
        md5_reading(params.ifd, &params, 64, &iters);
    }
    if (ft_strcmp(params.cipher, "md5") == 0)
  		init_md5_vectors(&iters);
  	if (ft_strcmp(params.cipher, "sha256") == 0)
  		init_sha256_vectors(&iters);
  	if (ft_strcmp(params.cipher, "sha512") == 0)
  		init_sha512_vectors(&iters);
      i = 0;
      while (i < 128)
        params.md5_buf[i++] = 0;
      params.bytes_read = 0;
    if  ((find_symb(params.flags, 's', FLAG_LEN) < 0 && params.ifd < 1) && find_symb(params.flags, 'p', FLAG_LEN) < 0)
    {
      //printf("%s\n", "INPUT");
      if (ft_strcmp(params.cipher, "sha512") == 0)
      md5_reading(0, &params, 128, &iters);
      else
      md5_reading(0, &params, 64, &iters);
    }

}
i = 0;

  while (i < params.if_no_file)
  {
    printf("md5: %s: No such file or directory\n", params.argvs[i]);
    i++;
  }
  if (params.ifd > 1)
    close(params.ifd);
		return (0);

}
