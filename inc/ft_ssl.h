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
#include <string.h>

#include "utils.h"

enum
{
	shaSuccess,
	shaNull,			/* Null pointer parameter */
	shaInputTooLong,	/* input data too long */
	shaStateError,		/* called Input after FinalBits or Result */
	shaBadParam			/* passed a bad parameter */
};

enum
{
	print,
	quiet,
	reverse,
	string,
	usage,
	dec,
	enc,
	in_file,
	out_file,
	is_pipe,
	md5,
	sha256,
	base64
};

#define PRINT	1 << print
#define QUIET	1 << quiet
#define REVERSE	1 << reverse
#define STRING	1 << string
#define USAGE	1 << usage
#define DECODE	1 << dec
#define ENCODE	1 << enc
#define IN_FILE	1 << in_file
#define OUT_FILE 1 << out_file
#define IS_PIPE	1 << is_pipe
#define MD5		1 << md5
#define SHA256	1 << sha256
#define BASE64	1 << base64

#define BASE64STR	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_"

#define SHA256_HSSZ 32
#define SHA256_BLSZ	64
#define MD5_HSSZ 	16

typedef struct	s_data
{
	const char	algostr[3][7];
	uint16_t	options;
	char		*pipe;
	char		**inputs;
	char		*in_file;
	char		*out_file;
}				t_data;

typedef struct SHA256_CTX
{
	uint32_t Intermediate_Hash[SHA256_HSSZ / 4]; /* Message Digest */
	uint32_t Length_Low;                /* Message length in bits */
	uint32_t Length_High;               /* Message length in bits */
	int_least16_t Message_Block_Index;  /* Message_Block array index */
	uint8_t Message_Block[SHA256_BLSZ];
	int Computed;                       /* Is the digest computed? */
	int Corrupted;                      /* Is the digest corrupted? */
}				t_SHA256_CTX;

typedef struct MD5_CTX
{
	uint32_t	state[4];
	uint32_t	count[2];
	uint8_t		buffer[64];
}				t_MD5_CTX;

// utils.c
void	decode(uint32_t *output, uint8_t *input, uint32_t len);
void	encode(uint8_t *output, uint32_t *input, uint32_t len);
char	*file_to_str(const char *filename);

//	display.c
void	header_display(FILE *stream, uint16_t options, const char *name, const char *to_hash);
void	MDPrint (const uint8_t digest[16]);
void	hash_display(FILE *stream, const uint8_t digest[16], uint16_t options, const char *name, const char *to_hash);
void	display(const uint8_t *digest, const t_data *data, const char *infilename, const char *to_hash);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//	parser.c
bool	parser(char **argv, t_data *data);

//	sha256.c
extern int		SHA256Reset(t_SHA256_CTX *);
extern int		SHA256Input(t_SHA256_CTX *, const uint8_t *bytes, unsigned int bytecount);
extern int		SHA256FinalBits(t_SHA256_CTX *, const uint8_t bits, unsigned int bitcount);
extern uint8_t	SHA256Result(t_SHA256_CTX *, uint8_t Message_Digest[SHA256_HSSZ]);// 
bool			SHAString(const t_data *data, const char *infilename, const char *to_hash);

//	md5.c
void	MD5Init(t_MD5_CTX *context);
void	MD5Transform(uint32_t state[4], uint8_t block[64]);
void	MD5Update(t_MD5_CTX *context, uint8_t *input, unsigned int inputLen);
void	MD5Final(uint8_t digest [16], t_MD5_CTX *context);
void	MD5memset(uint8_t *output, const uint8_t value, const uint32_t len);
uint8_t	*MD5memcpy(uint8_t *dest, const uint8_t *src, const uint32_t len);
void	MDString(const t_data *data, const char *infilename, const char *to_hash);

//	base64.c
char	*base64_encode(const char *input);
char	*base64_decode(const char *input);
char 	*B64String(const t_data *data, const char *to_hash);

//	routine.c
void	routine(t_data *data);

//	main.c
char 	*read_stdin( void );
bool	is_in_pipe( void );

#endif