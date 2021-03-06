#include <stdio.h>

unsigned long long sha512_cycle_shift(unsigned long long nbr, int count)
{
  int i = 0;
  int j = 0;
	unsigned long long tmp;
	long long bits[32];
	//printf("111%d\n", (*iters).a0);
		tmp = nbr;
  /*printf("UUU%llu\n", tmp);
	while (i < count)
	{
		bits[i] = (((unsigned long long)1) << j) & tmp;
    printf("UUU%llu\n", tmp);
		j++;
		i++;
	}
	tmp >>= count;
	//tmp %= 4294967296;
  printf("TTT%llu\n", tmp);
	i = 0;
	j = 64 - count;
	while (i < count)
	{
		if (bits[i])
	    tmp |= (((unsigned long long)1) << j);
	  else
	    tmp &= ~(((unsigned long long)1) << j);
		i++;
		j++;
	}*/
  return (nbr >> count) | (nbr << (63 - count));
		//printf("222%d\n", (*iters).a0);
}

unsigned int sha256_cycle_shift(unsigned int nbr, int count)
{
  int i = 0;
  int j = 0;
	unsigned int tmp;
	int bits[32];
	//printf("111%d\n", (*iters).a0);

		tmp = nbr;
	while (i < count)
	{
		bits[i] = (1 << j) & tmp;
    printf("%d\n", bits[i]);
		j++;
		i++;
	}
	tmp >>= count;
  printf("TTT%u\n", tmp);
	//tmp %= 4294967296;
  tmp &= 4294967295;
	i = 0;
	j = 32 - count;
  printf("TTT%u\n", j);
	while (i < count)
	{
		if (bits[i])
	    tmp |= (1 << j);
	  else
	    tmp &= ~(1 << j);
      printf("TTT%u\n", tmp);
		i++;
		j++;
	}
	return (tmp);
		//printf("222%d\n", (*iters).a0);
}

void md5_cycle_shift(unsigned long *a0, int count)
{
  int i = 0;
  int j = 0;
	unsigned long tmp;
  unsigned long tmp1;
	int bits[32];
	//printf("111%d\n", (*iters).a0);
	tmp = *a0;

	j = 31;
	while (i < count)
	{
		bits[i] = (1 << j) & tmp;
    printf("%d\n", bits[i]);
		j--;
		i++;
	}
  printf("TTT%lu\n", tmp);
	tmp <<= count;
  tmp1 = tmp % 4294967296;
  printf("TTT%lu\n", tmp);
	i = 0;
	j = count - 1;
  printf ("JJJ%d\n", j);
	while (j >= 0)
	{
		if (bits[i])
	    tmp1 |= (1 << j);
	  else
	    tmp1 &= ~(1 << j);
		i++;
		j--;
	}
	*a0 = tmp1;
		//printf("222%d\n", (*iters).a0);
}

int main(void)
{
  /*long test;

  test = (4023233417 & 2562383102) + (!(4023233417) & 271733878);
  printf("%lu\n", test);*/
  /*unsigned long test;
  test = 1138166207;
  printf("%lu\n", test);
  md5_cycle_shift(&test, 7);
  printf("%lu\n", test);*/
  //unsigned long test = 2636577670;
  //2487416768280023388
  unsigned long long test = 0x428a2f98d728ae22;
  test = (test & 0x00000000FFFFFFFF) << 32 | (test & 0xFFFFFFFF00000000) >> 32;
  test = (test & 0x0000FFFF0000FFFF) << 16 | (test & 0xFFFF0000FFFF0000) >> 16;
  test = (test & 0x00FF00FF00FF00FF) << 8  | (test & 0xFF00FF00FF00FF00) >> 8;
  /*printf("%llu\n", sha512_cycle_shift(test, 7));
  printf("%llu\n", sha512_cycle_shift(test, 20));
  printf("%llu\n", sha512_cycle_shift(test, 7) ^ sha512_cycle_shift(test, 20));
  printf("%ld\n", 2487416768280023388 ^ 5003802825750842738);*/
  //test = 3470005196;
  printf("%llx\n", test);



  /*unsigned int tmp1;
  unsigned int tmp2;
  unsigned long long test;
  tmp1 = (((('h' << 24) & 4294967295) +
    (('e' << 16) & 16777215)
+ (('l' << 8) & 65535) + ('l' & 255)));
tmp2 =
(((('o' << 24) & 4294967295) +
(('w' << 16) & 16777215)
+ (('o' << 8) & 65535) + ('\n' & 255)));
tmp1 = (((('a' << 24) & 4294967295) +
  (('b' << 16) & 16777215)
+ (('c' << 8) & 65535) + (0 & 255)));
tmp2 =
((((0 << 24) & 4294967295) +
((0 << 16) & 16777215)
+ ((0 << 8) & 65535) + (0 & 255)));
  test = (((unsigned long)tmp1) << 32) + (tmp2 & 4294967295);
  printf("%u\n", tmp1);
  printf("%u\n", tmp2);
      printf("%llu\n", test);*/

  //printf("%lx\n", (((test & 255) << 24) | ((test & 65535) << 8)) | (test >> 24));
//0110100001100101011011000110110001101111011101110110111100001010
  // 1101000011001010110110001101100 1101111011101110110111100001010
  //printf("%lx\n", (((((test & 255) << 24) | ((test & 65535) << 8)) | ((test) >> 16)) | (test & 255) << 8 /*| ((test & 4294967295) >> 24*/));
  /*printf("%lx\n", ((test >> 24) | ((test >> 8) & 0x0000ff00) | ((test<<8) & 0x00ff0000) | (test<<24)));
printf("%lx\n", ((test>>24)&255) | // move byte 3 to byte 0
                    ((test<<8)&16711680) | // move byte 1 to byte 2
                    ((test>>8)&65280) | // move byte 2 to byte 1
                    ((test<<24)&4278190080));*/
  //printf("%ld\n", ((((111 << 24) & 4294967295) + (('W' << 16) & 16777215) + ((' ' << 8) & 65535) + ('o' & 255))));

    /*printf("%lx\n", (((test & 255) << 24)));
      printf("%lx\n", (((test & 16777215) >> 16)));
        printf("%lx\n", (((test & 16777215) >> 16)));
          printf("%lx\n", (((test & 16777215) >> 16)));*/
  //printf("%lx\n", (((test & 255) << 24) + (test >> 32)));
}
/*01000011110101110000100110111111
0100001 1110101110000100110111111
11101011100001001101111110100001*/
/*01101010000010011110011001100111 01101010000010011110011001100111
01101010000010011110011001100111
 110101000001001111001100
 1     010101000001001111001100*/
 /*void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
 {
 	clear_iterators(iters);
 	while (((*iters).k = read(fd, &params->md5_buf, len)) > 0)
 	{
 		(*params).bytes_read += (*iters).k;
 		if ((*iters).k < len)
 			add_padding_md5(params, len, (*params).bytes_read);
 		if (ft_strcmp((*params).cipher, "md5") == 0)
 			start_md5(params, iters);
 		if (ft_strcmp((*params).cipher, "sha256") == 0)
 		{
 			if ((*iters).k == len)
 				start_sha256(params, iters, 1);
 			else
 			start_sha256(params, iters, 0);
 		}
 	}
 	if (ft_strcmp((*params).cipher, "md5") == 0)
 	{
 		if ((*iters).k == 0 && (*params).bytes_read % 64 == 0)
 		{
 			add_padding_md5(params, len, (*params).bytes_read);
 			start_md5(params, iters);
 		}
 		print_md5_result(iters, params);
 		init_md5_vectors(iters);
 	}
 	if (ft_strcmp((*params).cipher, "sha256") == 0)
 	{
 		if ((*iters).k == 0 && (*params).bytes_read % 64 == 0)
 		{
 			add_padding_md5(params, len, (*params).bytes_read);
 			start_sha256(params, iters, 0);
 		}
 		ft_printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
 		(*iters).f0, (*iters).h0);
 		init_sha256_vectors(iters);
 	}
  count.j = 0;
	while (count.j < 64)
		(*params).md5_buf[count.j++] = 0;
 }*/
