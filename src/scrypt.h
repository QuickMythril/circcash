#ifndef SCRYPT_H
#define SCRYPT_H
#include <stdlib.h>
#include <stdint.h>


static const int SCRYPT_SCRATCHPAD_SIZE = 131072 + 63;

void scrypt_1024_1_1_256(const char *input, char *output);
void scrypt_1024_1_1_256_sp_generic(const char *input, char *output, char *scratchpad);

#if defined(USE_SSE2)
#if defined(_M_X64) || defined(__x86_64__) || defined(_M_AMD64) || (defined(MAC_OSX) && defined(__i386__))
#define USE_SSE2_ALWAYS 1
#define scrypt_1024_1_1_256_sp(input, output, scratchpad) scrypt_1024_1_1_256_sp_sse2((input), (output), (scratchpad))
#else
#define scrypt_1024_1_1_256_sp(input, output, scratchpad) scrypt_1024_1_1_256_sp_detected((input), (output), (scratchpad))
#endif

void scrypt_detect_sse2();
void scrypt_1024_1_1_256_sp_sse2(const char *input, char *output, char *scratchpad);
extern void (*scrypt_1024_1_1_256_sp_detected)(const char *input, char *output, char *scratchpad);
#else
#define scrypt_1024_1_1_256_sp(input, output, scratchpad) scrypt_1024_1_1_256_sp_generic((input), (output), (scratchpad))
#endif

void
PBKDF2_SHA256(const uint8_t *passwd, size_t passwdlen, const uint8_t *salt,
    size_t saltlen, uint64_t c, uint8_t *buf, size_t dkLen);

static inline uint32_t le32dec(const void *pp)
{
        const uint8_t *p = (uint8_t const *)pp;
        return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
            ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}

static inline void le32enc(void *pp, uint32_t x)
{
        uint8_t *p = (uint8_t *)pp;
        p[0] = x & 0xff;
        p[1] = (x >> 8) & 0xff;
        p[2] = (x >> 16) & 0xff;
        p[3] = (x >> 24) & 0xff;
}
#endif

void fastcyclelfsr(unsigned char hash[32],uint32_t &cc,uint32_t &dd);

void cyclelfsr(unsigned char hash[32],uint32_t &cc,uint32_t &dd);

bool testequality(uint32_t cc,uint32_t oldcc,uint32_t dd,uint32_t olddd);
uint32_t hashspincc(uint32_t x);

uint32_t hashspindd(uint32_t x);

uint32_t hashspinrecombine(uint32_t cc,uint32_t dd);

void hashspinfinal(const char *input,uint32_t x, char *output);

void bitrotate_forward(uint32_t &x, uint32_t &len);
void bitrotate_reverse(uint32_t &x, uint32_t &len);

void hashspinlfsr_forward(uint32_t &cc, uint32_t &dd,unsigned char input[32]);
void hashspinlfsr_reverse(uint32_t &cc, uint32_t &dd,unsigned char input[32]);

void roundmap_forward(int *x, int *y);
void roundmap_reverse(int *x, int *y);

void basefunction_forward(int *hash, int *x, int *y);
void basefunction_reverse(int *hash, int *x, int *y);

void readoff_forward(int *x, int *y, int *w);
void readoff_reverse(int *x, int *y, int *w);

void spreadfifteen_forward(int &x, int *y);
void spreadfifteen_reverse(int &x, int *y);

void spreadseventeen_forward(int &x, int *y);
void spreadseventeen_reverse(int &x, int *y);

void hashspread_forward(int *hashbytes, int *hashbits);
void hashspread_reverse(int *hashbytes, int *hashbits);

void bhashspinlfsr_forward(int &cc, int &dd, int *hash);
void bhashspinlfsr_reverse(int &cc, int &dd, int *hash);


void revcyclelfsr(unsigned char hash[32],uint32_t &cc,uint32_t &dd);



