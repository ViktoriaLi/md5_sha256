/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_ssl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:45:51 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/11 15:45:54 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

void	flags_normalize(char *all_flags, t_args *params, int len)
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

void	when_file_found(char **argv, t_args *params, int i, int argc)
{
	int j;

	j = 0;
	(*params).filename = argv[i++];
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
			i++;
			j++;
		}
		(*params).if_no_file = j;
		(*params).argvs[j] = NULL;
	}
}

int		save_ssl_flags(char **argv, t_addition *iters, t_args *params,
char **all_flags)
{
	(*all_flags)[(*iters).j] = argv[(*iters).i][1];
	if (argv[(*iters).i][1] == 's' && argv[(*iters).i + 1])
	{
		(*params).md5_str = (unsigned char *)argv[(*iters).i + 1];
		(*iters).i++;
	}
	else if (argv[(*iters).i][1] == 's')
	{
		ft_printf("%s: option requires an argument -- s\n", argv[1]);
		ft_printf("%s\n", "usage: md5 [-pqr] [-s string] [files ...]");
		return (1);
	}
	(*iters).j++;
	(*iters).i++;
	return (0);
}

int		check_md5_and_sha256_flags(int argc, char **argv, t_args *params,
t_addition *iters)
{
	char		*all_flags;

	(*iters).i = 2;
	if (!(all_flags = (char *)malloc(argc - 1)))
		return (1);
	all_flags[argc - 1] = 0;
	while ((*iters).i < argc)
	{
		if (ft_strcmp(argv[(*iters).i], "-p") == 0 ||
		ft_strcmp(argv[(*iters).i], "-q") == 0 || ft_strcmp(argv[(*iters).i], "-r")
		== 0 || ft_strcmp(argv[(*iters).i], "-s") == 0)
		{
			if (save_ssl_flags(argv, iters, params, &all_flags))
				return (1);
		}
		else if (((*params).ifd = open(argv[(*iters).i], O_RDONLY)) > 0)
		{
			when_file_found(argv, params, (*iters).i, argc);
			break ;
		}
		else
			ft_printf("md5: %s: No such file or directory\n", argv[(*iters).i]);
	}
	flags_normalize(all_flags, params, argc - 1);
	return (0);
}
