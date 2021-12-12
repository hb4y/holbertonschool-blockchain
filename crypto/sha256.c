#include "hblk_crypto.h"

/**
 * sha256 - hash
 * @s: string
 * @len: len
 * @digest: hash dig
 * Return: digest
 */
uint8_t *sha256(int8_t const *s, size_t len,
				uint8_t digest[SHA256_DIGEST_LENGTH])
{
	SHA256_CTX context;

	if (!SHA256_Init(&context))
		return (NULL);
	if (!SHA256_Update(&context, (unsigned char *)s, len))
		return (NULL);
	if (!SHA256_Final(digest, &context))
		return (NULL);

	return (digest);
}
