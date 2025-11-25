#ifndef FTSSL
#define FTSSL

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PRINT	1
#define QUIET	1 << 1
#define REVERSE	1 << 2
#define STRING	1 << 3
#define USAGE	1 << 4
#define MD5		1 << 5
#define SHA256	1 << 6
#define IS_PIPE	1 << 7

typedef struct	s_data
{
	uint8_t	options;
	char	*pipe;
	char	**inputs;
}				t_data;

typedef struct MD5_CTX
{
	uint32_t	state[4];
	uint32_t	count[2];
	uint8_t		buffer[64];
}				t_MD5_CTX;

//	operations.c
uint32_t f(uint32_t x, uint32_t y, uint32_t z);
uint32_t g(uint32_t x, uint32_t y, uint32_t z);
uint32_t h(uint32_t x, uint32_t y, uint32_t z);
uint32_t i(uint32_t x, uint32_t y, uint32_t z);
uint32_t rot_left(uint32_t x, uint32_t n);
uint32_t ff(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
uint32_t gg(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
uint32_t hh(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
uint32_t ii(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);

// utils.c
void	decode(uint32_t *output, uint8_t *input, uint32_t len);
void	encode(uint8_t *output, uint32_t *input, uint32_t len);
void	MD5memset(uint8_t *output, const uint8_t value, const uint32_t len);
uint8_t	*MD5memcpy(uint8_t *dest, const uint8_t *src, const uint32_t len);
char	*file_to_str(char *filename);

//	display.c
void	header_display(uint8_t options, const char *name, const char *to_hash);
void	MDPrint (const uint8_t digest[16]);
void	MDdisplay(const uint8_t digest[16], uint8_t options, const char *name, const char *to_hash);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//	parser.c
bool	parser(char **argv, uint8_t *options, char ***inputs);

//	md5.c
void	MD5Init(t_MD5_CTX *context);
void	MD5Transform(uint32_t state[4], uint8_t block[64]);
void	MD5Update(t_MD5_CTX *context, uint8_t *input, unsigned int inputLen);
void	MD5Final(uint8_t digest [16], t_MD5_CTX *context);

//	main.c
void 	decode(uint32_t *output, uint8_t *input, uint32_t len);
void 	encode(uint8_t *output, uint32_t *input, uint32_t len);
void	MDString(const uint8_t options, const char *name, const char *to_hash);
char 	*get_input(uint8_t *options);

#endif