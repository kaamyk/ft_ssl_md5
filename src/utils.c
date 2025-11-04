#include "../inc/ft_ssl_md5.h"
#include <stdint.h>

unsigned char *MD5memcpy(unsigned char *dest, unsigned char *src, const uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

void	MD5memset(char *output, char value, uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		output[i] = value;
	}
}