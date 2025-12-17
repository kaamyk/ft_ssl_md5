#ifndef	BASE64_H
#define	BASE64_H

#include <stdint.h>

//	base64.c
char	*base64_encode(const char *input);
char	*base64_decode(const char *input);
char 	*B64String(const uint16_t options, const char *out, const char *to_hash);

#endif