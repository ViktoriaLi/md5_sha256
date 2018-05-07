#include <stdio.h>

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
  unsigned int test = 0x6A09E667;
  printf("%u\n", sha256_cycle_shift(test, 7));
  test = 3470005196;
  printf("%d\n", test);

  //printf("%lx\n", (((test & 255) << 24) | ((test & 65535) << 8)) | (test >> 24));

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
