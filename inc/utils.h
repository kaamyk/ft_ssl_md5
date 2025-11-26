#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define ROTL(bits, word)	\
	(((word) << (bits)) | ((word) >> (32-(bits))))
#define ROTR(bits, word)\
	(((word) >> (bits)) | ((word) << (32-(bits))))
#define SHTR(x, n)		\
	((x) >> (n))

#endif