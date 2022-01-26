#include "blockchain.h"

/**
 * block_mine - miner
 * @block: pointer
 */
void block_mine(block_t *block)
{
	uint64_t i = 0;

	do {
		block->info.nonce = i;

		block_hash(block, block->hash);

		i++;

	} while (!hash_matches_difficulty(block->hash, block->info.difficulty));

}
