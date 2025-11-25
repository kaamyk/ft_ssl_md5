#include "../inc/ft_ssl.h"

// Basic MD5 functions
inline uint32_t f(uint32_t x, uint32_t y, uint32_t z){ return((x & y) | (~x & z)); }
inline uint32_t g(uint32_t x, uint32_t y, uint32_t z){ return((x & z) | (y & ~z)); }
inline uint32_t h(uint32_t x, uint32_t y, uint32_t z){ return (x ^ y ^ z); }
inline uint32_t i(uint32_t x, uint32_t y, uint32_t z){ return (y ^ (x | ~z)); }

inline uint32_t rot_left(uint32_t x, uint32_t n){ return ((x << n) | (x >> (32 - n))); }
inline uint32_t rot_right(uint32_t x, uint32_t n){ return ((x >> n) | (x << (32 - n))); }
inline uint32_t	sht_right(uint32_t x, uint32_t n){ return (x >> n); }

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
// /* Define the SHA SIGMA and sigma macros */
// #define SHA256_SIGMA0(word)   \
//   (SHA256_ROTR( 2,word) ^ SHA256_ROTR(13,word) ^ SHA256_ROTR(22,word))
// #define SHA256_SIGMA1(word)   \
//   (SHA256_ROTR( 6,word) ^ SHA256_ROTR(11,word) ^ SHA256_ROTR(25,word))
// #define SHA256_sigma0(word)   \
//   (SHA256_ROTR( 7,word) ^ SHA256_ROTR(18,word) ^ SHA256_SHR( 3,word))
// #define SHA256_sigma1(word)   \
//   (SHA256_ROTR(17,word) ^ SHA256_ROTR(19,word) ^ SHA256_SHR(10,word))
inline uint32_t sha256_SIGMA0(uint32_t word) { return (rot_right(2 , word) ^ rot_right(13, word) ^ rot_right(22, word)); }
inline uint32_t sha256_SIGMA1(uint32_t word) { return (rot_right(6 , word) ^ rot_right(11, word) ^ rot_right(25, word)); }
inline uint32_t sha256_sigma0(uint32_t word) { return (rot_right(7 , word) ^ rot_right(18, word) ^ sht_right(3 , word)); }
inline uint32_t sha256_sigma1(uint32_t word) { return (rot_right(17, word) ^ rot_right(19, word) ^ sht_right(10, word)); }