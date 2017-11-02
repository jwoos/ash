#ifndef ASH_VENDOR_HASH_H
#define ASH_VENDOR_HASH_H


#include <stdint.h>


uint64_t hashJDB2(unsigned char*);

uint64_t hashSBDM(unsigned char*);

void hashMurmur3_x86_32(const void*, const int, const uint32_t, void*);

void hashMurmur3_x86_128(const void*, const int, const uint32_t, void*);

void hashMurmur3_x64_128(const void*, const int, const uint32_t, void*);


#endif
