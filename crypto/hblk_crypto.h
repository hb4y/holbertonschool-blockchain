#ifndef blockchain
#define blockchain

#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <sys/stat.h>

#define EC_PUB_LEN 65
#define EC_CURVE   NID_secp256k1
#define PRI_FILENAME "key.pem"
#define PUB_FILENAME "key_pub.pem"

uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);
EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN]);
int ec_save(EC_KEY *key, char const *folder);

#endif
