/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/01/15 11:06:12 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFF_SIZE 32
# define FD_LIMIT 12288
# define STACK_LIMIT 8192000

int		get_next_line(const int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_strclr(char *s);
size_t	ft_strlen(const char *s);
void	ft_strdel(char **as);
void	if_next(char **line, char **tmp, char **next_s, int i);
int		if_n_found(char *buf, char **tmp, int ret, char **all_fd);
int		reading(char **line, char **all_fd, char **tmp, int fd);
void	swap_and_join(char **tmp, char *buf);

#endif
