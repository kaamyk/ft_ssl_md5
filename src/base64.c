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
	const char		pad[2] = {'=', '='};
	const uint32_t	input_l = strlen(input);
	uint32_t	tmp = 0;
	uint32_t	i = 0;
	uint32_t	j = 0;
	char		*res = NULL;
	
	if (!input_l)
	{
		res = calloc(1, 1);
		return (res);
	}
	res = calloc( (((input_l / 3) + need_pad(input_l)) * 4) + 1, 1);
	while (i + 2 < input_l)
	{
		tmp = input[i] << 16 | input[i + 1] << 8 | input[i + 2];
		printf("tmp == %d\n", tmp);
		res[j]		= get_base_char(tmp >> 18);
		res[j + 1]	= get_base_char(tmp >> 12);
		res[j + 2]	= get_base_char(tmp >> 6);
		res[j + 3]	= get_base_char(tmp);
		printf("res = [%s]\n", res);
		i += 3;
		j += 4;
	}
	ft_strlcpy(res + (((input_l / 3) + need_pad(input_l)) * 4), pad, (input_l % 3) - 3);
	printf("final res == [%s]\n", res);
	return res;
}