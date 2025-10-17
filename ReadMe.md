# FT_SSL
> This project is about recreating the crypographic hash functions **md5** and **sha256**.

## Summary:
- [Theory](#theory)
	- [Definitions](#definitions)
	- [More details](#more-details)
	- [The method](#the-method)
- [In practice](#in-practice)

## Theory
### Definitions
Cryptographic hash function : it is a mathematical algorithm that maps data of arbitrary size to a bit string of a fixed size.
Md5 (Message Digest version 5): hash function producing a 128-bit hash value.
Sha256 (Secure Hash Algorithm 256-bit) : hash function producing a 256-bit hash value, whose digest is eight 32-bit words.
Message digest :
Round : in cryptograhy, it refers to one iteration of the iternal transformation process applied by the algorithm.

### More details
#### Md5:
Md5 was designed in 1991 to replace an earlier hash function md4 and was specified in 1992.
It was used as cryptographic hash function but it has been found that it suffers from multiple vulnerabilities. They are mainly collisions. For example in 2012, the Flame malware could fake a Microsoft digital signature. It remains suitable to use for non cryptographic uses and might be prefered due to its lower computational requirements.

#### Sha256:
Sha256 is part of the SHA-2 algorithms family containing 6 hash functions : SHA-224, SHA-256, SHA-384, SHA-512, SHA-512/224 and SHA-512/256. SHA-2 were designed by the NSA and published in 2001.
The SHA-2 showed some weakness but a hash made with 64 rounds of sha-256 never been cracked.

### The method
*From RFC-1321*.  
#### Md5:
**Step 1 : Bit padding**  
The message should be padded so that its length is 64 bits shorter than a multiple of 512 (bits).  

**Step 2 : Append length**  
The 64 bits missing are filled filled with the 64-bit value of the total length of the message **before** padding.  

**Step 3 : Buffer initialization**  
- Create **4 buffers** (A, B, C and D), each with a bit length of 32. They will be initiated as follows:
	- A: 0x01234567
	- B: 0x89ABCDEF
	- C: 0xFEDCBA89
	- D: 0x76543210  

- **step 4 : Message processing**  
	- Define **4 functions** :
		- F(X, Y, Z) = (X & Y) | (!X & Z)
		- G(X, Y, Z) = (X & Y) | (X & !Z)
		- H(X, Y, Z) = (X ^ Y ^ Z)
		- I(X, Y, Z) = Y ^ (X | !Z)
	- Create a 64 constant elements table. These 64 values are dfined following a formula as follows:  
		When passed to sin() function i must be in radian.  
	```
	for (i = 0; i < 64; i++):  
		T[i] = 2^32 * abs(sin(i))  
	```
	- Define 4 variables (AA, BB, CC and DD) to store values of A, B, C and D for later.  
	- Split message in list of 16-bit blocks (see RFC for more).  
	- Save A, B, C and D as AA, BB, CC and DD.
- **step 5 : Rounds**

