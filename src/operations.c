#include "../inc/ft_ssl_md5.h"
#include <stdint.h>

// Basic MD5 functions
inline int16_t f(int16_t x, int16_t y, int16_t z){ return((x & y) | (~x & z)); }
inline int16_t g(int16_t x, int16_t y, int16_t z){ return((x & z) | (y & ~z)); }
inline int16_t h(int16_t x, int16_t y, int16_t z){ return (x ^ y ^ z); }
inline int16_t i(int16_t x, int16_t y, int16_t z){ return (y ^ (x | z)); }

inline int16_t rot_left(int x, uint8_t n){ return ((x << n) | (x >> (32 - n))); }

inline uint16_t ff(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac)
{
	a += f(b, c, d) + x + (uint32_t)ac;
	a = rot_left(a, s);
	a += b;
	return a;
}

inline uint16_t gg(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac)
{
	a += g(b, c, d) + x + (uint32_t)ac;
	a = rot_left(a, s);
	a += b;
	return a;
}

inline uint16_t hh(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac)
{
	a += h(b, c, d) + x + (uint32_t)ac;
	a = rot_left(a, s);
	a += b;
	return a;
}

inline uint16_t ii(int16_t a, int16_t b, int16_t c, int16_t d, int16_t x, int16_t s, uint32_t ac)
{
	a += i(b, c, d) + x + (uint32_t)ac;
	a = rot_left(a, s);
	a += b;
	return a;
}