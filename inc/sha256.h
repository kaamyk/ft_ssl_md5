#ifndef SHA256_H
#define SHA256_H

#include "ft_ssl.h"

#define SHA256_BLSZ	64
#define SHA256_HSSZ	32

#define CH (x, y, z)(((x) & (y)) ^ ((~x) & z))
#define MAJ(x, y, z)(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define BSIG0(x)	((SHA256_ROTR(2, x)) ^ (SHA256_ROTR(13, x)) ^ SHA256_ROTR(22, x))
#define BSIG1(x)	((SHA256_ROTR(6, x)) ^ (SHA256_ROTR(11, x)) ^ SHA256_ROTR(25, x))
#define SSIG0(x)	((SHA256_ROTR(7, x)) ^ (SHA256_ROTR(18, x)) ^ SHA256_ROTR(3, x))
#define SSIG1(x)	((SHA256_ROTR(17, x)) ^ (SHA256_ROTR(19, x)) ^ SHA256_ROTR(10, x))

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

enum {
	shaSuccess = 0,
	shaNull,			/* Null pointer parameter */
	shaInputTooLong,	/* input data too long */
	shaStateError,		/* called Input after FinalBits or Result */
	shaBadParam			/* passed a bad parameter */
};

//	sha256.c
extern int	SHA256Reset(t_SHA256_CTX *);
extern int	SHA256Input(t_SHA256_CTX *, const uint8_t *bytes, unsigned int bytecount);
extern int	SHA256FinalBits(t_SHA256_CTX *, const uint8_t bits, unsigned int bitcount);
extern int	SHA256Result(t_SHA256_CTX *, uint8_t Message_Digest[SHA256_HSSZ]);// 

#endif