#ifndef SHA256_H
#define SHA256_H

#include "utils.h"

#define SHA256_BLSZ	64
#define SHA256_HSSZ	32

// #define CH (x, y, z)(((x) & (y)) ^ ((~x) & z))
// #define MAJ(x, y, z)(((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
// #define BSIG0(x)	((rotate_right(2, x)) ^ (rotate_right(13, x)) ^ rotate_right(22, x))
// #define BSIG1(x)	((rotate_right(6, x)) ^ (rotate_right(11, x)) ^ rotate_right(25, x))
// #define SSIG0(x)	((rotate_right(7, x)) ^ (rotate_right(18, x)) ^ rotate_right(3, x))
// #define SSIG1(x)	((rotate_right(17, x)) ^ (rotate_right(19, x)) ^ rotate_right(10, x))

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
extern int		SHA256Reset(t_SHA256_CTX *);
extern int		SHA256Input(t_SHA256_CTX *, const uint8_t *bytes, unsigned int bytecount);
extern int		SHA256FinalBits(t_SHA256_CTX *, const uint8_t bits, unsigned int bitcount);
extern uint8_t	SHA256Result(t_SHA256_CTX *, uint8_t Message_Digest[SHA256_HSSZ]);// 

#endif