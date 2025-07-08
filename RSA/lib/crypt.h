#ifndef CRYPT_H
#define CRYPT_H
#include<math.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define SEGMENTED_SIZE 32768
#define SET_BIT(arr, i) (arr[(i) >> 3] |= (1 << ((i) & 7)))
#define CLEAR_BIT(arr, i) (arr[(i) >> 3] &= ~(1 << ((i) & 7)))
#define GET_BIT(arr, i) ((arr[(i) >> 3] >> ((i) & 7)) & 1)
typedef struct{
    int d;
    int x;
    int y;
} Result;

int mcd(int a, int b);
Result Euclidean(int a,int b);
void segmentedSieve(int n);
void sieve_odd_bitset(int limit,int** primes,int *prime_count);
uint64_t mod_exp(uint64_t n,uint64_t exp,uint64_t mod);
int is_probable_prime(uint64_t n,uint64_t k);
uint64_t random_odd_integer(int bits);
#endif 