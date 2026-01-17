#ifndef CRYPT_H
#define CRYPT_H
#include <locale.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>

#define SEGMENTED_SIZE 32768
#define SET_BIT(arr, i) (arr[(i) >> 3] |= (1 << ((i) & 7)))
#define CLEAR_BIT(arr, i) (arr[(i) >> 3] &= ~(1 << ((i) & 7)))
#define GET_BIT(arr, i) ((arr[(i) >> 3] >> ((i) & 7)) & 1)
typedef struct {
  uint64_t d;
  int64_t x;
  int64_t y;
} Result;
typedef struct message {
  size_t capacity;
  size_t size;
  wchar_t *message;
  uint64_t *encrypted;
  wchar_t *decrypted;
  int key;
} message;

message getMessage();
uint64_t mcd(uint64_t a, uint64_t b);
Result Euclidean(uint64_t a, uint64_t b);
void segmentedSieve(int n);
void sieve_odd_bitset(int limit, int **primes, int *prime_count);
uint64_t mod_exp(uint64_t n, uint64_t exp, uint64_t mod);
int is_probable_prime(uint64_t n, uint64_t k);
uint64_t random_odd_integer(int bits);
uint64_t generate_prime(int bit_length, int k);
#endif
