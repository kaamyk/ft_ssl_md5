#ifndef FTSSL
#define FTSSL

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "md5.h"
#include "sha256.h"

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


//	operations.c
// uint32_t	f(uint32_t x, uint32_t y, uint32_t z);
// uint32_t	g(uint32_t x, uint32_t y, uint32_t z);
// uint32_t	h(uint32_t x, uint32_t y, uint32_t z);
// uint32_t	i(uint32_t x, uint32_t y, uint32_t z);
// uint32_t	rot_left(uint32_t x, uint32_t n);
// uint32_t	rot_right(uint32_t x, uint32_t n);
// uint32_t	sht_right(uint32_t x, uint32_t n);
// uint32_t	ff(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
// uint32_t	gg(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
// uint32_t	hh(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
// uint32_t	ii(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac);
// uint32_t	SHA256_SIGMA0(uint32_t word);
// uint32_t	SHA256_SIGMA1(uint32_t word);
// uint32_t	SHA256_sigma0(uint32_t word);
// uint32_t	SHA256_sigma1(uint32_t word);

// utils.c
void	decode(uint32_t *output, uint8_t *input, uint32_t len);
void	encode(uint8_t *output, uint32_t *input, uint32_t len);
char	*file_to_str(char *filename);

//	display.c
void	header_display(uint8_t options, const char *name, const char *to_hash);
void	MDPrint (const uint8_t digest[16]);
void	display(const uint8_t digest[16], uint8_t options, const char *name, const char *to_hash);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//	parser.c
bool	parser(char **argv, uint8_t *options, char ***inputs);

//	main.c
void	MDString(const uint8_t options, const char *name, const char *to_hash);
char 	*get_input( void );

#endif