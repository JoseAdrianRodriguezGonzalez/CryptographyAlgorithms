#include "./lib/crypt.h"
#include <cstdint>
#include <math.h>
#include <stdint.h>
#include <sys/types.h>
typedef struct {
  uint64_t p;
  uint64_t M;
  uint64_t q;
} Field;
typedef struct {
  Field f;
  uint64_t g;
  uint64_t h;
} publicKey;
typedef struct {
  uint64_t c;
} privateKey;
typedef struct {
  privateKey private_;
  publicKey public_;
} Key;
Field FieldGenerator(int bitLength);

Field FieldGenerator(int bitLength) {
  Field key = {};

  uint64_t p, M, q;
  do {
    p = generate_prime(bitLength, 10);
    M = random_odd_integer(bitLength);
    q = p * M + 1;
  } while (!is_probable_prime(q, 40));
  key.p = p;
  key.M = M;
  key.q = q;
  return key;
}
Key ElGammalEncrypt(int bitLength) {
  Field F = FieldGenerator(bitLength);
  uint64_t f, g;
  do {
    f = random_odd_integer(bitLength);
    g = mod_exp(f, F.M, F.q);
  } while (g == 1);
  uint64_t c;
  do {
    c = random_odd_integer(bitLength);
  } while (c == 0 || c >= F.p);
  uint64_t h = mod_exp(g, c, F.q);
  publicKey p = {F, g, h};
  privateKey P = {c};
  Key k = {P, p};
  return k;
}
void ELGammalEncryption(message *m, publicKey p, int bitLength) {
  uint64_t k;
  do {
    k = random_odd_integer(bitLength);
  } while (k > p.f.p - 1);
  uint64_t x1 = mod_exp(p.g, k, p.f.q);
  uint64_t x2 = (x * mod_exp(p.h, k, p.f.q)) % p.f.q;
}
