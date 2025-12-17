#include "../inc/ft_ssl.h"

inline char get_base_char(uint8_t to_convert) { return (BASE64STR[to_convert & 0x3F]); }

inline bool need_pad(const uint32_t input_l) { return (input_l % 3 > 0); }

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	srclen;

	i = 0;
	srclen = strlen(src);
	if (!size)
		return (srclen);
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

char	*base64_encode(char *input)
{
	printf("Input == [%s]\n", input);
	// const char		pad[2] = {'=', '='};
	const uint32_t	input_l = strlen(input);
	const uint32_t	alloc_l = (((input_l / 3) + need_pad(input_l)) * 4);
	uint32_t	tmp = 0;
	char		*res = NULL;
	
	if (!input_l)
	{
		res = calloc(1, 1);
		return (res);
	}
	printf("calloc(%d)\n", alloc_l + 1);
	res = calloc(alloc_l + 1, 1);
	if (!res)
		return (NULL);
	for (uint32_t k = 0, i = 0; k < alloc_l; k += 4, i += 3)
	{
		tmp = 0;
		for (uint8_t j = 0; j < 3 && i + j < input_l; j++)
				tmp |= input[i + j] << (16 - (j * 8));
		res[k] = get_base_char(tmp >> 18);
		res[k + 1] = get_base_char(tmp >> 12);
		res[k + 2] = (tmp >> 6) & 0x3F ? get_base_char(tmp >> 6) : '=';
		res[k + 3] = tmp & 0x3F ? get_base_char(tmp) : '=';
	}
	printf("tmp == %d\n", tmp);
	printf("final res == [%s]\n", res);
	return res;
}