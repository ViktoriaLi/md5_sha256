/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 18:21:51 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

# define FLAG_LIMIT 8

typedef struct		s_argc
{
	char	*one_arg;
	int		flag[FLAG_LIMIT];
	int		width;
	int		star_width;
	int		res;
	char	length[3];
	int		precision;
	char	specifier;
	char	*left;
	int		left_len;
	char	*reserve;
	char	sign;
}					t_argc;

typedef struct		s_forprint
{
	int			len;
	int			lenf;
	int			spaces;
	int			zeros;
	char		*s;
	char		*sf;
	wchar_t		*us;
}					t_forprint;

int					ft_printf(const char *format, ...);
int					check_specifier(char type, t_argc *params, int *i);
void				check_length(char *length, int *i, char *dest);
void				check_length_hlzj(int *j, int len, char *length,
					char **dest);
void				check_length_hhll(int h_count, int l_count, char **dest);
void				check_flags(char *str, int *i, int *flag);
void				argument_analize(t_argc *params, va_list ap);
void				argument_save(int i, char *argv, t_argc *params,
					va_list ap);
void				struct_init(t_argc *params);
void				check_star_anywhere(char c, int *i, int *param);
int					if_percent_found(const char *format, t_argc *params,
					int *i);
void				specifier_finder(t_argc *params, char *argv, int *i,
					va_list ap);
int					medium_flags(char argv, int *i, t_argc *params);

void				s_analizator(t_argc *params, va_list ap);
void				us_analizator(t_argc *params, va_list ap);
void				d_analizator(t_argc *params, va_list ap);
void				o_analizator(t_argc *params, va_list ap);
void				u_analizator(t_argc *params, va_list ap);
void				x_analizator(t_argc *params, va_list ap);
void				c_analizator(t_argc *params, va_list ap);
void				uc_analizator(t_argc *params, va_list ap);
void				n_analizator(t_argc *params, va_list ap);

int					if_flag(int *all_flags, int flag, int j);
void				print_hex(char **res, uintmax_t nbr, t_argc params,
					unsigned int base);
void				check_stars(t_argc *params, va_list ap);
void				int_depend_length(intmax_t *d, char *length,
					t_argc *params);
void				ox_depend_length(intmax_t *d, char *length, t_argc *params);
void				u_depend_length(uintmax_t *d, char *length, t_argc *params);
void				print_params_left(char *s, t_argc *params, int zeros,
					int spaces);
void				print_params_right(char *s, t_argc *params, int zeros,
					int spaces);
void				print_unicode(wchar_t *test, int len, t_argc *params);
int					if_percent_found(const char *format, t_argc *params,
					int *i);
void				specifier_finder(t_argc *params, char *argv, int *i,
					va_list ap);
int					precision_finder(char *argv, int *i, t_argc *params);
void				print_left(t_argc *params);
void				elems_init(t_forprint *elems);
void				o_printing(char *s, t_argc *params, int zeros, int spaces);
void				o_elems_count(t_argc *params, t_forprint *elems,
					intmax_t d);
void				if_space_flag(t_argc *params, int *zeros, int *spaces);
void				print_spaces(t_argc *params, int *zeros, int *spaces);
void				save_flags(int *tmp, int **flag, int j);
void				int_elems_count(t_argc *params, t_forprint *elems);
void				check_spec_cond_us(t_argc *params, t_forprint *elems);
void				print_add_text(const char *format, int *i, t_argc *params);

int					ft_strcmp(const char *s1, const char *s2);
int					ft_printf_atoi(const char *str);
void				ft_strdel(char **as);
size_t				ft_strlen_wide(wchar_t *s);
size_t				ft_strlen(const char *s);
void				ft_putstr(char const *s);
char				*ft_printf_itoa(intmax_t n);
char				*ft_uns_itoa(uintmax_t n);
char				*ft_len_strnstr(char *big, char *little, size_t len);
char				*ft_strsub(char const *s, unsigned int start, size_t len);

#endif
