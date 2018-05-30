/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_ssl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:45:51 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/13 15:46:25 by vlikhotk         ###   ########.fr       */
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
	free(all_flags);
}

void	when_file_found(char **argv, t_args *params, int i, int argc)
{
	(*params).filename = argv[i++];
	if (i < argc)
		(*params).if_no_file = i;
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
	(*all_flags)[(*iters).j] = 0;
	return (0);
}

char	*check_md5_and_sha256_flags(int argc, char **argv, t_args *params,
t_addition *iters)
{
	char		*all_flags;

	(*iters).i = 2;
	all_flags = ft_strnew(argc - 1);
	while ((*iters).i < argc)
	{
		if (ft_strcmp(argv[(*iters).i], "-p") == 0 ||
		ft_strcmp(argv[(*iters).i], "-q") == 0 || ft_strcmp(argv[(*iters).i],
		"-r") == 0 || ft_strcmp(argv[(*iters).i], "-s") == 0)
		{
			if (save_ssl_flags(argv, iters, params, &all_flags))
				return (NULL);
		}
		else if (((*params).ifd = open(argv[(*iters).i], O_RDONLY)) > 0)
		{
			when_file_found(argv, params, (*iters).i, argc);
			break ;
		}
		else
		{
			ft_printf("md5: %s: No such file or directory\n", argv[(*iters).i]);
			return (NULL);
		}
	}
	return (all_flags);
}
