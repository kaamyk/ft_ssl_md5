#ifndef MD5_H
#define MD5_H

#include "utils.h"

#define MD5_HSSZ 16

typedef struct MD5_CTX
{
	uint32_t	state[4];
	uint32_t	count[2];
	uint8_t		buffer[64];
}				t_MD5_CTX;

//	md5.c
void	MD5Init(t_MD5_CTX *context);
void	MD5Transform(uint32_t state[4], uint8_t block[64]);
void	MD5Update(t_MD5_CTX *context, uint8_t *input, unsigned int inputLen);
void	MD5Final(uint8_t digest [16], t_MD5_CTX *context);
void	MD5memset(uint8_t *output, const uint8_t value, const uint32_t len);
uint8_t	*MD5memcpy(uint8_t *dest, const uint8_t *src, const uint32_t len);
#endif