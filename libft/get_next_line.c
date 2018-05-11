/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 13:24:07 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/01/15 11:05:52 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	swap_and_join(char **tmp, char *buf)
{
	char *swap;

	swap = NULL;
	swap = *tmp;
	*tmp = ft_strjoin(swap, buf);
	if (swap[0])
		ft_strdel(&swap);
}

void	if_next(char **line, char **tmp, char **next_s, int i)
{
	char	*rem;

	while ((*next_s)[i] != '\n' && (*next_s)[i] != '\0')
		i++;
	if ((*next_s)[i] == '\n')
	{
		*line = ft_strsub((*next_s), 0, i);
		if (i != (int)ft_strlen((*next_s)) && (*next_s)[i + 1])
		{
			rem = (*next_s);
			(*next_s) = ft_strsub((*next_s), i + 1, ft_strlen((*next_s)) - i);
			ft_strdel(&rem);
		}
		else
		{
			if ((*next_s))
				ft_strdel(next_s);
		}
	}
	else
	{
		swap_and_join(tmp, (*next_s));
		ft_strdel(next_s);
	}
}

int		if_n_found(char *buf, char **tmp, int ret, char **all_fd)
{
	int		i;
	char	*rem;

	i = 0;
	rem = NULL;
	while (i < ret && buf[i] != '\n')
		i++;
	if ((buf[i] == '\n' || (i == ret && i != BUFF_SIZE)))
	{
		rem = ft_strsub(buf, 0, i);
		swap_and_join(tmp, rem);
		ft_strdel(&rem);
		if ((ret - i - 1) > 0)
		{
			rem = *all_fd;
			*all_fd = ft_strsub(buf, i + 1, ret - i - 1);
			ft_strdel(&rem);
		}
		return (1);
	}
	return (0);
}

int		reading(char **line, char **all_fd, char **tmp, int fd)
{
	int		i;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*swap;

	swap = NULL;
	while ((ret = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		if ((i = if_n_found(buf, tmp, ret, &all_fd[fd])))
		{
			if (i == ret)
				ft_strdel(all_fd);
			*line = *tmp;
			return (1);
		}
		else
			swap_and_join(tmp, buf);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int					res;
	char				*tmp;
	char				*buf;
	static char			*all_fd[FD_LIMIT];

	res = 0;
	tmp = "";
	buf = NULL;
	if (fd < 0 || fd > FD_LIMIT || BUFF_SIZE < 1 || BUFF_SIZE > STACK_LIMIT ||
		!line || read(fd, buf, 0) < 0)
		return (-1);
	*line = NULL;
	if (all_fd[fd])
		if_next(line, &tmp, &all_fd[fd], res);
	if (*line)
		return (1);
	res = reading(line, all_fd, &tmp, fd);
	if (tmp[0] != 0)
	{
		*line = tmp;
		return (1);
	}
	return (res);
}
