#include "../inc/ft_ssl_md5.h"
#include <stdint.h>

// Basic MD5 functions
inline uint32_t f(uint32_t x, uint32_t y, uint32_t z){ return((x & y) | (~x & z)); }
inline uint32_t g(uint32_t x, uint32_t y, uint32_t z){ return((x & z) | (y & ~z)); }
inline uint32_t h(uint32_t x, uint32_t y, uint32_t z){ return (x ^ y ^ z); }
inline uint32_t i(uint32_t x, uint32_t y, uint32_t z){ return (y ^ (x | ~z)); }

inline uint32_t rot_left(uint32_t x, uint32_t n){ return ((x << n) | (x >> (32 - n))); }

inline uint32_t ff(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a += f(b, c, d) + x + ac;
	a = rot_left(a, s);
	a += b;
	return a;
}

inline uint32_t gg(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a += g(b, c, d) + x + ac;
	a = rot_left(a, s);
	a += b;
	return a;
}

inline uint32_t hh(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a += h(b, c, d) + x + ac;
	a = rot_left(a, s);
	a += b;
	return a;
}

inline uint32_t ii(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac)
{
	a += i(b, c, d) + x + ac;
	a = rot_left(a, s);
	a += b;
	return a;
}