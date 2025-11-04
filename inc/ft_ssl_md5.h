#ifndef FTSSL
#define FTSSL

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct MD5_CTX
{
	uint32_t	state[4];
	uint64_t	count;
	char		buffer[64];
}				t_MD5_CTX;

//	operations.c
int16_t f(int16_t x, int16_t y, int16_t z);
int16_t g(int16_t x, int16_t y, int16_t z);
int16_t h(int16_t x, int16_t y, int16_t z);
int16_t i(int16_t x, int16_t y, int16_t z);
int16_t rot_left(int x, uint8_t n);
uint16_t ff(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac);
uint16_t gg(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac);
uint16_t hh(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac);
uint16_t ii(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac);

// utils.c
void	MD5memset(char *output, char value, uint32_t len);
unsigned char *MD5memcpy(char *dest, char *src, const uint32_t len);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//	parser.c
bool	parser(int argc, char **argv, uint8_t *options);

#endif