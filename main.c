/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 13:47:06 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/11 15:55:44 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		if_valid_args(int argc, char **argv, t_args *params, t_addition *iters)
{
	int res;

	res = 0;
	if (argc == 1)
	{
		ft_printf("%s ", "usage: ft_ssl command");
		ft_printf("%s\n", "[command opts] [command args]");
		return (0);
	}
	if (ft_strcmp(argv[1], "md5") != 0 && ft_strcmp(argv[1], "sha256")
		!= 0 && ft_strcmp(argv[1], "sha512") != 0)
	{
		ft_printf("ft_ssl: Error: %s is an invalid command.\n\n", argv[1]);
		ft_printf("%s\n", "Standard commands:\n\nMessage Digest commands:");
		ft_printf("%s\n", "md5\nsha256\n\nCipher commands:\n");
		return (0);
	}
	if ((ft_strcmp(argv[1], "md5") == 0) &&
		(res = check_md5_and_sha256_flags(argc, argv, params, iters)) > 0)
		return (0);
	else if ((ft_strcmp(argv[1], "sha256") == 0 || ft_strcmp(argv[1], "sha512")
	== 0) && (res = check_md5_and_sha256_flags(argc, argv, params, iters)) > 0)
		return (0);
	(*params).cipher = argv[1];
	return (1);
}

void	vectors_initiation(t_args *params, t_addition *iters)
{
	int i;

	i = 0;
	if (ft_strcmp((*params).cipher, "md5") == 0)
		init_md5_vectors(iters);
	if (ft_strcmp((*params).cipher, "sha256") == 0)
		init_sha256_vectors(iters);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		init_sha512_vectors(iters);
	while (i < 128)
		(*params).md5_buf[i++] = 0;
	(*params).bytes_read = 0;
}

int		main(int argc, char **argv)
{
	int			i;
	int			len;
	t_addition	iters;
	t_args		params;

	i = 0;
	clear_iterators(&iters);
	clear_struct(&params);
	if (!if_valid_args(argc, argv, &params, &iters))
		return (0);
	if (ft_strcmp(params.cipher, "sha512") == 0)
		len = 128;
	else
		len = 64;
	vectors_initiation(&params, &iters);
	reading_cases(&params, &iters, len);
	i = 0;
	while (i < params.if_no_file)
	{
		ft_printf("md5: %s: No such file or directory\n", params.argvs[i]);
		i++;
	}
	if (params.ifd > 1)
		close(params.ifd);
	//free(params.argvs);
	return (0);
}
