#include "blockchain.h"

/**
 * block_is_valid - is valid
 * @block: pointer
 * @prev_block: pointer
 * Return: 0 or 1
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	uint8_t buff[SHA256_DIGEST_LENGTH] = {0};
	block_t const _gen = GENESIS_BLOCK;

	if (!block || (!prev_block && block->info.index != 0))
		return (1);

	if (block->info.index == 0)
		return (memcmp(block, &_gen, sizeof(_gen)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);

	if (!block_hash(prev_block, buff) ||
		memcmp(buff, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);

	if (!block_hash(block, buff) ||
		memcmp(buff, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);

	return (0);

}
