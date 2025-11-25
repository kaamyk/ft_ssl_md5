#include "../inc/ft_ssl_md5.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

void decode(uint32_t *output, uint8_t *input, uint32_t len)
{
	for (uint32_t i = 0, j = 0; j < len; i++, j += 4)
	{
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) | (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
	}
}

void encode(uint8_t *output, uint32_t *input, uint32_t len)
{
	for (uint32_t i = 0, j = 0; j < len; i++, j += 4)
	{
		output[j] = (uint8_t)(input[i] & 0xff);
		output[j + 1] = (uint8_t)((input[i] >> 8) & 0xff);
		output[j + 2] = (uint8_t)((input[i] >> 16) & 0xff);
		output[j + 3] = (uint8_t)((input[i] >> 24) & 0xff);
	}
}

void	MD5Init(t_MD5_CTX *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

void	MD5Transform(uint32_t state[4], uint8_t block[64])
{
	uint32_t	a = state[0];
	uint32_t	b = state[1];
	uint32_t	c = state[2];
	uint32_t	d = state[3];
	uint32_t	x[16] = {0};
	
	decode(x, block, 64);
	
	/* Round 1 */
	a = ff(a, b, c, d, x[ 0],  7, 0xd76aa478); /* 1 */
	d = ff(d, a, b, c, x[ 1], 12, 0xe8c7b756); /* 2 */
	c = ff(c, d, a, b, x[ 2], 17, 0x242070db); /* 3 */
	b = ff(b, c, d, a, x[ 3], 22, 0xc1bdceee); /* 4 */
	a = ff(a, b, c, d, x[ 4],  7, 0xf57c0faf); /* 5 */
	d = ff(d, a, b, c, x[ 5], 12, 0x4787c62a); /* 6 */
	c = ff(c, d, a, b, x[ 6], 17, 0xa8304613); /* 7 */
	b = ff(b, c, d, a, x[ 7], 22, 0xfd469501); /* 8 */
	a = ff(a, b, c, d, x[ 8],  7, 0x698098d8); /* 9 */
	d = ff(d, a, b, c, x[ 9], 12, 0x8b44f7af); /* 10 */
	c = ff(c, d, a, b, x[10], 17, 0xffff5bb1); /* 11 */
	b = ff(b, c, d, a, x[11], 22, 0x895cd7be); /* 12 */
	a = ff(a, b, c, d, x[12],  7, 0x6b901122); /* 13 */
	d = ff(d, a, b, c, x[13], 12, 0xfd987193); /* 14 */
	c = ff(c, d, a, b, x[14], 17, 0xa679438e); /* 15 */
	b = ff(b, c, d, a, x[15], 22, 0x49b40821); /* 16 */
	
	/* Round 2 */
	a = gg(a, b, c, d, x[ 1],  5, 0xf61e2562); /* 17 */
	d = gg(d, a, b, c, x[ 6],  9, 0xc040b340); /* 18 */
	c = gg(c, d, a, b, x[11], 14, 0x265e5a51); /* 19 */
	b = gg(b, c, d, a, x[ 0], 20, 0xe9b6c7aa); /* 20 */
	a = gg(a, b, c, d, x[ 5],  5, 0xd62f105d); /* 21 */
	d = gg(d, a, b, c, x[10],  9,  0x2441453); /* 22 */
	c = gg(c, d, a, b, x[15], 14, 0xd8a1e681); /* 23 */
	b = gg(b, c, d, a, x[ 4], 20, 0xe7d3fbc8); /* 24 */
	a = gg(a, b, c, d, x[ 9],  5, 0x21e1cde6); /* 25 */
	d = gg(d, a, b, c, x[14],  9, 0xc33707d6); /* 26 */
	c = gg(c, d, a, b, x[ 3], 14, 0xf4d50d87); /* 27 */
	b = gg(b, c, d, a, x[ 8], 20, 0x455a14ed); /* 28 */
	a = gg(a, b, c, d, x[13],  5, 0xa9e3e905); /* 29 */
	d = gg(d, a, b, c, x[ 2],  9, 0xfcefa3f8); /* 30 */
	c = gg(c, d, a, b, x[ 7], 14, 0x676f02d9); /* 31 */
	b = gg(b, c, d, a, x[12], 20, 0x8d2a4c8a); /* 32 */
	
	/* Round 3 */
	a = hh(a, b, c, d, x[ 5],  4, 0xfffa3942); /* 33 */
	d = hh(d, a, b, c, x[ 8], 11, 0x8771f681); /* 34 */
	c = hh(c, d, a, b, x[11], 16, 0x6d9d6122); /* 35 */
	b = hh(b, c, d, a, x[14], 23, 0xfde5380c); /* 36 */
	a = hh(a, b, c, d, x[ 1],  4, 0xa4beea44); /* 37 */
	d = hh(d, a, b, c, x[ 4], 11, 0x4bdecfa9); /* 38 */
	c = hh(c, d, a, b, x[ 7], 16, 0xf6bb4b60); /* 39 */
	b = hh(b, c, d, a, x[10], 23, 0xbebfbc70); /* 40 */
	a = hh(a, b, c, d, x[13],  4, 0x289b7ec6); /* 41 */
	d = hh(d, a, b, c, x[ 0], 11, 0xeaa127fa); /* 42 */
	c = hh(c, d, a, b, x[ 3], 16, 0xd4ef3085); /* 43 */
	b = hh(b, c, d, a, x[ 6], 23,  0x4881d05); /* 44 */
	a = hh(a, b, c, d, x[ 9],  4, 0xd9d4d039); /* 45 */
	d = hh(d, a, b, c, x[12], 11, 0xe6db99e5); /* 46 */
	c = hh(c, d, a, b, x[15], 16, 0x1fa27cf8); /* 47 */
	b = hh(b, c, d, a, x[ 2], 23, 0xc4ac5665); /* 48 */
	
	/* Round 4 */
	a = ii(a, b, c, d, x[ 0],  6, 0xf4292244); /* 49 */
	d = ii(d, a, b, c, x[ 7], 10, 0x432aff97); /* 50 */
	c = ii(c, d, a, b, x[14], 15, 0xab9423a7); /* 51 */
	b = ii(b, c, d, a, x[ 5], 21, 0xfc93a039); /* 52 */
	a = ii(a, b, c, d, x[12],  6, 0x655b59c3); /* 53 */
	d = ii(d, a, b, c, x[ 3], 10, 0x8f0ccc92); /* 54 */
	c = ii(c, d, a, b, x[10], 15, 0xffeff47d); /* 55 */
	b = ii(b, c, d, a, x[ 1], 21, 0x85845dd1); /* 56 */
	a = ii(a, b, c, d, x[ 8],  6, 0x6fa87e4f); /* 57 */
	d = ii(d, a, b, c, x[15], 10, 0xfe2ce6e0); /* 58 */
	c = ii(c, d, a, b, x[ 6], 15, 0xa3014314); /* 59 */
	b = ii(b, c, d, a, x[13], 21, 0x4e0811a1); /* 60 */
	a = ii(a, b, c, d, x[ 4],  6, 0xf7537e82); /* 61 */
	d = ii(d, a, b, c, x[11], 10, 0xbd3af235); /* 62 */
	c = ii(c, d, a, b, x[ 2], 15, 0x2ad7d2bb); /* 63 */
	b = ii(b, c, d, a, x[ 9], 21, 0xeb86d391); /* 64 */
	
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	
	/* Zeroize sensitive information.*/
	MD5memset((uint8_t *)x, 0, sizeof (x));
}

void MD5Update(t_MD5_CTX *context, uint8_t *input, unsigned int inputLen)
{
	uint32_t	i = 0;
	uint32_t	partLen = 0;
	uint64_t	index = 0;
	
	/* Compute number of bytes mod 64 */
	index = (uint32_t)((context->count[0] >> 3) & 0x3F);
	/* Update number of bits */
	if ((context->count[0] += ((uint32_t)inputLen << 3)) < ((uint32_t)inputLen << 3))
		context->count[1]++;
	context->count[1] += ((uint32_t)inputLen >> 29);
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

void	MD5Final(uint8_t digest [16], t_MD5_CTX *context)
{
	uint8_t		padding[64] = {0x80, 0x0};
	uint8_t		bits[8];
	uint32_t	index = 0;
	uint32_t	padLen = 0;
	
	//	Save number of bits
	encode(bits, context->count, 8);
	
	//	Pad out to 56 mod 64
	index = (uint32_t)((context->count[0] >> 3) & 0x3f);
	if (index < 56)
		padLen = 56 - index;	// 64 - 8
	else
		padLen = 120 - index;	// 128 - 8
	MD5Update(context, padding, padLen);
	MD5Update(context, bits, 8);
	encode(digest, context->state, 16);
	MD5memset((uint8_t *)context, 0, sizeof(*context));
}

char 	*get_input(uint8_t *options)
{
	char		buf[256] = {0};
	char	*tmp = NULL;
	char	*input = calloc(1, 1);
	if (input == NULL)
	{
		fprintf(stderr, "Fatal Error: calloc: %s\n", strerror(errno));
		return (NULL);
	}
	
	while (read(STDIN_FILENO, buf, 255) > 0)
	{
		*options |= IS_PIPE;
		tmp = input;
		if ((input = ft_strjoin(input, buf)) == NULL)
		{
			fprintf(stderr, "Fatal Error: ft_strjoin(): %s\n", strerror(errno));
			return (NULL);
		}
		free(tmp);
	}
	return (input);
}

void	MDString(const uint8_t options, const char *name, const char *to_hash)
{
	uint8_t		digest[16] = {0};
	t_MD5_CTX	context = {0};
	
	MD5Init(&context);
	MD5Update(&context, (uint8_t *)to_hash, strlen(to_hash));
	MD5Final(digest, &context);
	if (!(options & QUIET))
	{
		if (options & IS_PIPE)
		{
			if (options & PRINT)
				printf("(\"%s\") = ", to_hash);
			else
				write(STDOUT_FILENO, "(stdin)= ", 10);
		}
		else
		{
			write(STDOUT_FILENO, "MD5 ", 4);
			if (options & STRING)
				printf ("(\"%s\")= ", to_hash);
			else
				printf ("(%s)= ", name);
		}
	}
	MDPrint (digest);
	printf ("\n");
}

void	print_args(char **argv)
{
	for (uint8_t i = 0; argv[i] != NULL; i++)
	{
		printf("argv[%d] == %s\n", i, argv[i]);
	}
}

void	launch_algo(t_data data)
{
	char	*file_content = NULL;
	
	if (data.options & USAGE)
	{
		write(STDOUT_FILENO, "ft_ssl usage:\n\techo string | ./ft_ssl algorithm [options] [-s \"string\"] arguments\nalgorithm values : selects the hash algorithm to run\n\tsha256\n\tmd5\noptions: \n\tsets the display format :\n\t\t-p : print stdin to stdout and append the checksum to stdout.\n\t\t-q : quiet mode\n\t\t-r : reverse the format of the ouput\n\t-s : print the sum of the given string. Any argument after this option is consider as a string. Each argument after the string is consider as a filename (see arguments section).\n\t-h : print usage\narguments :\n\t Each is considered has a file name. The command tries to open each file, is it fails it goes on.\n", 615);
	}
	else if (data.options & MD5)
	{
		if (data.options & IS_PIPE)
		{
			MDString(data.options, NULL, data.pipe);
			data.options &= ~(IS_PIPE);
		}
		if (data.options & STRING)
		{
			MDString(data.options, NULL, *(data.inputs++));
			data.options &= ~(STRING);
		}
		while (*data.inputs != NULL)
		{
			file_content = file_to_str(*data.inputs);
			if (file_content != NULL)
				MDString(data.options, *data.inputs, file_content);
			free(file_content);
			data.inputs++;
		}
	}
	// else if (data.options & SHA256)
	// 	SHAString(input);
}

void	print_arguments(char **argv)
{
	printf("================\n");
	printf("**argv:\n");
	while (*argv != NULL)
	{
		printf("\t%s\n", *(argv++));
	}
	printf("================\n");
}

int		main( int argc, char **argv )
{
	t_data	data = {0};
	
	(void) argc;
	
	print_arguments(argv);
	if (parser(argv, &data.options, &data.inputs) == 1)
	{
		free(data.pipe);
		return (1);
	}
	data.pipe = get_input(&data.options);
	if (data.pipe == NULL)
		return (1);
	launch_algo(data);
	free(data.pipe);
	return (0);
}