#include "../inc/ft_ssl_md5.h"
#include <string.h>
#include <unistd.h>

void	MD5Init(t_MD5_CTX *context)
{
	context->count = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

static void decode(uint32_t *output, char *input, uint32_t len)
{
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
	{
		output[i] = ((uint32_t) input[j]) | (((uint32_t) input[j + 1]) << 8) | (((uint32_t) input[j + 2]) << 16) | (((uint32_t) input[j + 3]) << 24);
	}
}

void	MD5Transform(uint32_t state[4], char block[64])
{
	uint32_t	a = state[0];
	uint32_t	b = state[1];
	uint32_t	c = state[2];
	uint32_t	d = state[3];
	uint32_t	x[16] = {0};
	
	decode(x, block, 64);
	
	/* Round 1 */
	ff (a, b, c, d, x[ 0], 7, 0xd76aa478); /* 1 */
	ff (d, a, b, c, x[ 1], 12, 0xe8c7b756); /* 2 */
	ff (c, d, a, b, x[ 2], 17, 0x242070db); /* 3 */
	ff (b, c, d, a, x[ 3], 22, 0xc1bdceee); /* 4 */
	ff (a, b, c, d, x[ 4], 7, 0xf57c0faf); /* 5 */
	ff (d, a, b, c, x[ 5], 12, 0x4787c62a); /* 6 */
	ff (c, d, a, b, x[ 6], 17, 0xa8304613); /* 7 */
	ff (b, c, d, a, x[ 7], 22, 0xfd469501); /* 8 */
	ff (a, b, c, d, x[ 8], 7, 0x698098d8); /* 9 */
	ff (d, a, b, c, x[ 9], 12, 0x8b44f7af); /* 10 */
	ff (c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
	ff (b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
	ff (a, b, c, d, x[12], 7, 0x6b901122); /* 13 */
	ff (d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
	ff (c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
	ff (b, c, d, a, x[15], 22, 0x49b40821); /* 16 */
	
	/* Round 2 */
	gg (a, b, c, d, x[ 1], 5, 0xf61e2562); /* 17 */
	gg (d, a, b, c, x[ 6], 9, 0xc040b340); /* 18 */
	gg (c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
	gg (b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /* 20 */
	gg (a, b, c, d, x[ 5], 5, 0xd62f105d); /* 21 */
	gg (d, a, b, c, x[10], 9,  0x2441453); /* 22 */
	gg (c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
	gg (b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /* 24 */
	gg (a, b, c, d, x[ 9], 5, 0x21e1cde6); /* 25 */
	gg (d, a, b, c, x[14], 9, 0xc33707d6); /* 26 */
	gg (c, d, a, b, x[ 3], 14, 0xf4d50d87); /* 27 */
	gg (b, c, d, a, x[ 8], 20, 0x455a14ed); /* 28 */
	gg (a, b, c, d, x[13], 5, 0xa9e3e905); /* 29 */
	gg (d, a, b, c, x[ 2], 9, 0xfcefa3f8); /* 30 */
	gg (c, d, a, b, x[ 7], 14, 0x676f02d9); /* 31 */
	gg (b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */
	
	/* Round 3 */
	hh (a, b, c, d, x[ 5], 4, 0xfffa3942); /* 33 */
	hh (d, a, b, c, x[ 8], 11, 0x8771f681); /* 34 */
	hh (c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
	hh (b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
	hh (a, b, c, d, x[ 1], 4, 0xa4beea44); /* 37 */
	hh (d, a, b, c, x[ 4], 11, 0x4bdecfa9); /* 38 */
	hh (c, d, a, b, x[ 7], 16, 0xf6bb4b60); /* 39 */
	hh (b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
	hh (a, b, c, d, x[13], 4, 0x289b7ec6); /* 41 */
	hh (d, a, b, c, x[ 0], 11, 0xeaa127fa); /* 42 */
	hh (c, d, a, b, x[ 3], 16, 0xd4ef3085); /* 43 */
	hh (b, c, d, a, x[ 6], 23,  0x4881d05); /* 44 */
	hh (a, b, c, d, x[ 9], 4, 0xd9d4d039); /* 45 */
	hh (d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
	hh (c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
	hh (b, c, d, a, x[ 2], 23, 0xc4ac5665); /* 48 */
	
	/* Round 4 */
	ii (a, b, c, d, x[ 0], 6, 0xf4292244); /* 49 */
	ii (d, a, b, c, x[ 7], 10, 0x432aff97); /* 50 */
	ii (c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
	ii (b, c, d, a, x[ 5], 21, 0xfc93a039); /* 52 */
	ii (a, b, c, d, x[12], 6, 0x655b59c3); /* 53 */
	ii (d, a, b, c, x[ 3], 10, 0x8f0ccc92); /* 54 */
	ii (c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
	ii (b, c, d, a, x[ 1], 21, 0x85845dd1); /* 56 */
	ii (a, b, c, d, x[ 8], 6, 0x6fa87e4f); /* 57 */
	ii (d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
	ii (c, d, a, b, x[ 6], 15, 0xa3014314); /* 59 */
	ii (b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
	ii (a, b, c, d, x[ 4], 6, 0xf7537e82); /* 61 */
	ii (d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
	ii (c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /* 63 */
	ii (b, c, d, a, x[ 9], 21, 0xeb86d391); /* 64 */
	
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	
	/* Zeroize sensitive information.*/
	MD5memset((char *)x, 0, sizeof (x));
}

void MD5Update(t_MD5_CTX *context, char *input, unsigned int inputLen)
{
	uint32_t	i = 0;
	uint32_t	partLen = 0;
	uint64_t	index = 0;
	
	/* Compute number of bytes mod 64 */
	index = (uint64_t)(context->count & 0x3F);
	/* Update number of bits */
	context->count += (uint64_t)inputLen << 3;
	partLen = 64 - index;
	/* Transform as many times as possible.*/
	if (inputLen >= partLen)
	{
		MD5memcpy(&context->buffer[index], input, partLen);
		MD5Transform (context->state, context->buffer);
		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform (context->state, &input[i]);
		index = 0;
	}
	else
		 i = 0;
	
	/* Buffer remaining input */
	MD5memcpy(&context->buffer[index], &input[i], inputLen-i);
}

char 	*get_input( void )
{
	char		buf[256] = {0};
	char	*tmp = NULL;
	char	*input = calloc(1, 1);
	if (input == NULL)
	{
		fprintf(stderr, "Fata Error: calloc: %s\n", strerror(errno));
		return (NULL);
	}
	
	while (read(STDIN_FILENO, buf, 255) > 0)
	{
		tmp = input;
		if ((input = ft_strjoin(input, buf)) == NULL)
		{
			fprintf(stderr, "Fatal Error: ft_strjoin(): %s\n", strerror(errno));
			return (NULL);
		}
		free(tmp);
	}
	printf("Input == [%s]\n", input);
	return (input);
}

int	main( int argc, char **argv )
{
	t_MD5_CTX	context = {0};
	// uint8_t		options = 0;
	char	*input = get_input();
	
	(void) argc;
	(void) argv;
	(void) input;
	
	// if (parser(argc, argv, &options) == 1)
	// 	return (1);
	MD5Init(&context);
	MD5Update(&context, input, strlen(input));
	// MDFinal();
	free(input);
	return (0);
}