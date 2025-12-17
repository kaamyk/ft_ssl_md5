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

#include "md5.h"
#include "sha256.h"
#include "base64.h"

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

typedef struct	s_data
{
	uint16_t	options;
	char		*pipe;
	char		**inputs;
}				t_data;

// utils.c
void	decode(uint32_t *output, uint8_t *input, uint32_t len);
void	encode(uint8_t *output, uint32_t *input, uint32_t len);
char	*file_to_str(char *filename);

//	display.c
void	header_display(uint16_t options, const char *name, const char *to_hash);
void	MDPrint (const uint8_t digest[16]);
void	display(const uint8_t digest[16], uint16_t options, const char *name, const char *to_hash);

// ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);

//	parser.c
bool	parser(char **argv, uint16_t *options, char ***inputs);

//	routine.c
void	MDString(const uint16_t options, const char *name, const char *to_hash);
bool	SHAString(const uint16_t options, const char *name, const char *to_hash);
void	launch_algo(uint16_t options, char *name, char* to_hash);
void	routine(t_data data);

//	main.c
char 	*read_stdin( void );
bool	is_in_pipe( void );

#endif