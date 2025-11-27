#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// #define rotate_left(bits, word)	\
// 	(((word) << (bits)) | ((word) >> (32-(bits))))
// #define rotate_right(bits, word)\
// 	(((word) >> (bits)) | ((word) << (32-(bits))))
// #define shift_right(x, n)		\
// 	((x) >> (n))


uint32_t	rotate_left(uint8_t bits, uint32_t word);
uint32_t	rotate_right(uint8_t bits, uint32_t word);
uint32_t	shift_right(uint8_t bits, uint32_t word);

#endif