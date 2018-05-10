#include "ft_ssl.h"

unsigned long long	cycle_shift(unsigned long long nbr, int count, int len)
{
	return (nbr >> count) | (nbr << (len - count));
}

void add_padding_md5(t_args *params, int len, int count)
{
	if (ft_strcmp((*params).cipher, "md5") == 0 || ft_strcmp((*params).cipher, "sha256") == 0)
	{
		if (count != 0 || (count == 0 && ((*params).bytes_read % 64 == 0)))
		(*params).md5_buf[count++] = 128;
   while (count < len)
     (*params).md5_buf[count++] = 0;
		 if (count < len - 8)
		 {
			 if (((*params).bytes_read * 8) <= 255)
		    	(*params).md5_buf[63] = (*params).bytes_read * 8;
		  	else
		  			(*params).md5_buf[63] = 0;
		 }
	}
	if (ft_strcmp((*params).cipher, "sha512") == 0)
	{
		if (count != 0 ||  (count == 0 && ((*params).bytes_read % 128 == 0)))
		(*params).md5_buf[count++] = 128;
   while (count < len)
     (*params).md5_buf[count++] = 0;
		 if (count < len - 16)
		 {
			 if (((*params).bytes_read * 8) <= 255)
		    	(*params).md5_buf[127] = (*params).bytes_read * 8;
		  	else
		  			(*params).md5_buf[127] = 0;
		 }
	}
}

void md5_cycle_shift(unsigned int *word, int count, int rounds, t_addition *iters)
{
	unsigned int tmp;
	int bits[32];
	clear_iterators(iters);
		tmp = *word;
	(*iters).j = 31;
	while ((*iters).i < count)
	{
		bits[(*iters).i] = (1 << (*iters).j) & tmp;
		(*iters).j--;
		(*iters).i++;
	}
	tmp <<= count;
	(*iters).i = 0;
	(*iters).j = count - 1;
	while ((*iters).j >= 0)
	{
		if (bits[(*iters).i])
	    tmp |= (1 << (*iters).j--);
	  else
	    tmp &= ~(1 << (*iters).j--);
		(*iters).i++;
	}
		*word = tmp;
}

unsigned long long made_words_for_sha512(t_args *params, t_addition *iters)
{
	unsigned int		tmp1;
	unsigned int		tmp2;
	unsigned long long	word;

	tmp1 = ((((*params).md5_buf[(*iters).k++] << 24) +
	((*params).md5_buf[(*iters).k++] << 16)
	+ ((*params).md5_buf[(*iters).k++] << 8) +
	(*params).md5_buf[(*iters).k++]));
	tmp2 = ((((*params).md5_buf[(*iters).k++] << 24) +
	((*params).md5_buf[(*iters).k++] << 16)
	+ ((*params).md5_buf[(*iters).k++] << 8) + (*params).md5_buf[(*iters).k++]));
	word = (((unsigned long long)tmp1) << 32) + (tmp2 & 4294967295);
	return (word);
}

unsigned int make_word_md5(int i, t_args *params, int iflast,
t_addition *iters)
{
	unsigned int tmp;

	if ((*iters).k == 59 && (*params).md5_buf[56] == 0 && !iflast)
	tmp = (*params).bytes_read * 8;
	else
	tmp = ((((*params).md5_buf[(*iters).k--] << 24) +
	((*params).md5_buf[(*iters).k--] << 16)
	+ ((*params).md5_buf[(*iters).k--] << 8) +
	(*params).md5_buf[(*iters).k]));
 	return (tmp);
}
