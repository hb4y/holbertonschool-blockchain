#include "blockchain.h"

/**
 * block_create - create
 * @prev: pointer
 * @data: pointer
 * @data_len: lenght
 * Return: pointer
 */
block_t *block_create(block_t const *prev, int8_t const *data,
	uint32_t data_len)
{
	block_t *b = calloc(1, sizeof(*b));

	if (!b)
		return (NULL);
	memcpy(&(b->data.buffer), data, MIN(data_len, BLOCKCHAIN_DATA_MAX));
	b->data.len = MIN(data_len, BLOCKCHAIN_DATA_MAX);
	b->info.index = prev->info.index + 1;
	b->info.timestamp = time(NULL);
	memcpy(&(b->info.prev_hash), prev->hash, SHA256_DIGEST_LENGTH);
	return (b);
}
