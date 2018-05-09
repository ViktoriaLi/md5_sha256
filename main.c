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
  if (params.ifd > 1)
    close(params.ifd);
		return (0);
}
