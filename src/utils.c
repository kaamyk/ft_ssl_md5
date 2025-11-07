#include "../inc/ft_ssl_md5.h"
#include <stdint.h>

uint8_t	*MD5memcpy(uint8_t *dest, const uint8_t *src, const uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

void	MD5memset(uint8_t *output, const uint8_t value, const uint32_t len)
{
	for (uint32_t i = 0; i < len; i++)
	{
		output[i] = value;
	}
}

void MDPrint (uint8_t digest[16])
{
	for (uint8_t i = 0; i < 16; i++)
	printf ("%02x", digest[i]);
}