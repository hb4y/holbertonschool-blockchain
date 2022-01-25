#include "blockchain.h"

/**
 * block_hash - hash
 * @block: pointer
 * @hash_buf: hash dig
 * Return: pointer
 */
uint8_t *block_hash(block_t const *block,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t largo = sizeof(block->info) + block->data.len;

	sha256((int8_t const *)&(block->info), largo, hash_buf);

	return (hash_buf);

}
