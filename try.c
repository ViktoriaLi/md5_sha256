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
  printf("%llu\n", sha512_cycle_shift(test, 7));
  printf("%llu\n", sha512_cycle_shift(test, 20));
  printf("%llu\n", sha512_cycle_shift(test, 7) ^ sha512_cycle_shift(test, 20));
  printf("%ld\n", 2487416768280023388 ^ 5003802825750842738);
  //test = 3470005196;
  printf("%llu\n", test);



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

 void start_sha256(t_args *params, t_addition *iters, int iflast)
 {
 	t_addition				count;
 	t_sha256				sha_add_vars;

 	const unsigned int square[64] = {0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

    unsigned int words[64];
 		clear_iterators(&count);
 	while (count.i < 16)
 	{
 		if ((*params).md5_buf[63] == 0 && count.i == 15 && !iflast)
 		words[count.i] = (*params).bytes_read * 8;
 		else
 		words[count.i] = (((((*params).md5_buf[count.k++] << 24) & 4294967295) +
 			(((*params).md5_buf[count.k++] << 16) & 16777215)
 + (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
 		//printf("WWW %u\n", words[count.i]);
 		count.i++;
 	}
 	while (count.i < 64)
 	{
 		sha_add_vars.s0 = sha256_cycle_shift(words[count.i-15], 7) ^ sha256_cycle_shift(words[count.i-15], 18)
 		^ (words[count.i-15] >> 3);
 sha_add_vars.s1 = sha256_cycle_shift(words[count.i-2], 17) ^ sha256_cycle_shift(words[count.i-2], 19) ^ (words[count.i-2] >> 10);
 		words[count.i] = words[count.i-16] + sha_add_vars.s0 + words[count.i-7] + sha_add_vars.s1;
 		count.i++;
 	}
 	(*iters).a1 = (*iters).a0;
 	(*iters).b1 = (*iters).b0;
 	(*iters).c1 = (*iters).c0;
 	(*iters).d1 = (*iters).d0;
 	(*iters).e1 = (*iters).e0;
 	(*iters).f1 = (*iters).f0;
 	(*iters).g1 = (*iters).g0;
 	(*iters).h1 = (*iters).h0;
 	//ft_printf("START%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
 	//(*iters).f1, (*iters).h1);

 	count.i = 0;
 	while (count.i < 64)
 	{
 		//ft_printf("FFF%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
 		//(*iters).f1, (*iters).h1);
 		sha_add_vars.eps0 = sha256_cycle_shift((*iters).a1, 2) ^ sha256_cycle_shift((*iters).a1, 13) ^ sha256_cycle_shift((*iters).a1, 22);
         sha_add_vars.ma = ((*iters).a1 & (*iters).b1) ^ ((*iters).a1 & (*iters).c1) ^ ((*iters).b1 & (*iters).c1);
         sha_add_vars.t2 = sha_add_vars.eps0 + sha_add_vars.ma;
         sha_add_vars.eps1 = sha256_cycle_shift((*iters).e1, 6) ^ sha256_cycle_shift((*iters).e1, 11) ^ sha256_cycle_shift((*iters).e1, 25);
         sha_add_vars.ch = ((*iters).e1 & (*iters).f1) ^ ((~(*iters).e1) & (*iters).g1);
         sha_add_vars.t1 = (*iters).h1 + sha_add_vars.eps1 + sha_add_vars.ch + square[count.i] + words[count.i];
 				//ft_printf("MMM%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
 				//(*iters).f1, (*iters).h1);
 		(*iters).h1 = (*iters).g1;
 		(*iters).g1 = (*iters).f1;
 		(*iters).f1 = (*iters).e1;
 		(*iters).e1 = (*iters).d1 + sha_add_vars.t1;
 		(*iters).d1 = (*iters).c1;
 		(*iters).c1 = (*iters).b1;
 		(*iters).b1 = (*iters).a1;
 		(*iters).a1 = sha_add_vars.t1 + sha_add_vars.t2;
 		//ft_printf("EEE%x %x %x %x %x %x %x %x \n", (*iters).a1, (*iters).b1, (*iters).c1, (*iters).d1, (*iters).e1, (*iters).f1,
 		//(*iters).f1, (*iters).h1);
 		count.i++;
 	}
 		(*iters).a0 += (*iters).a1;
 		(*iters).b0 += (*iters).b1;
 		(*iters).c0 += (*iters).c1;
 		(*iters).d0 += (*iters).d1;
 		(*iters).e0 += (*iters).e1;
 		(*iters).f0 += (*iters).f1;
 		(*iters).g0 += (*iters).g1;
 		(*iters).h0 += (*iters).h1;
 		//printf("START %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
 }
