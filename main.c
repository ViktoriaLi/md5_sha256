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

void	print_with_flags(int source, t_args *params, int place, char *cipher)
{
	if (place == 0)
	{
		if (source == 1 && find_symb((*params).flags, 's', FLAG_LEN) >= 0 &&
			find_symb((*params).flags, 'q', FLAG_LEN) < 0 &&
			find_symb((*params).flags, 'r', FLAG_LEN) < 0)
			ft_printf("%s (\"%s\") = ", cipher, (*params).md5_str);
		if (source == 0 && (*params).ifd > 0 &&
			find_symb((*params).flags, 'q', FLAG_LEN)
			< 0 && find_symb((*params).flags, 'r', FLAG_LEN) < 0)
			ft_printf("%s (%s) = ", cipher, (*params).filename);
	}
	if (place == 1)
	{
		if (source == 0 && (*params).ifd > 0 &&
			find_symb((*params).flags, 'r', FLAG_LEN)
			>= 0 && find_symb((*params).flags, 'q', FLAG_LEN) < 0)
			ft_printf(" %s\n", (*params).filename);
		else if (source == 1 && find_symb((*params).flags, 's', FLAG_LEN)
			>= 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0 &&
			find_symb((*params).flags, 'q', FLAG_LEN) < 0)
			ft_printf(" \"%s\"\n", (*params).md5_str);
		else
			ft_printf("%c", '\n');
	}
}

void	print_md5_result(t_addition *iters, t_args *params, int source)
{
	int				i;
	unsigned int	x[4];
	unsigned char	*y;

	i = 0;
	x[0] = (*iters).a0;
	x[1] = (*iters).b0;
	x[2] = (*iters).c0;
	x[3] = (*iters).d0;
	y = (unsigned char *)x;
	print_with_flags(source, params, 0, "MD5");
	while (i < 16)
	{
		if (y[i] < 16)
			ft_printf("0%x", y[i]);
		else
			ft_printf("%x", y[i]);
		i++;
	}
	print_with_flags(source, params, 1, "MD5");
}

int		if_valid_args(int argc, char **argv, t_args *params,
t_addition *iters)
{
	char *res;

	res = NULL;
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
		ft_printf("%s\n", "md5\nsha256\nsha512\n\nCipher commands:");
		return (0);
	}
	if (((ft_strcmp(argv[1], "md5") == 0 || ft_strcmp(argv[1], "sha256") == 0
	|| ft_strcmp(argv[1], "sha512") == 0) &&
	!(res = check_md5_and_sha256_flags(argc, argv, params, iters))))
		return (0);
	flags_normalize(res, params, argc - 1);
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

	clear_iterators(&iters);
	clear_struct(&params);
	if (!if_valid_args(argc, argv, &params, &iters))
		return (0);
	params.cipher = argv[1];
	if (ft_strcmp(params.cipher, "sha512") == 0)
		len = 128;
	else
		len = 64;
	vectors_initiation(&params, &iters);
	reading_cases(&params, &iters, len);
	i = params.if_no_file;
	if (i)
		while (i < argc)
		{
			ft_printf("md5: %s: No such file or directory\n", argv[i]);
			i++;
		}
	if (params.ifd > 1)
		close(params.ifd);
}
