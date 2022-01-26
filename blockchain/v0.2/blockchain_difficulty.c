#include "blockchain.h"

/**
 * blockchain_difficulty - set diff
 * @blockchain: pointer
 * Return: new diff
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *l_b, *new_b;
	uint64_t eta, rta;

	if (!blockchain)
		return (0);

	l_b = llist_get_tail(blockchain->chain);
	if (!l_b)
		return (0);

	if (l_b->info.index == 0 ||
		l_b->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL)
		return (l_b->info.difficulty);

	new_b = llist_get_node_at(blockchain->chain,
		l_b->info.index + 1 - DIFFICULTY_ADJUSTMENT_INTERVAL);

	eta = DIFFICULTY_ADJUSTMENT_INTERVAL * BLOCK_GENERATION_INTERVAL;
	rta = l_b->info.timestamp - new_b->info.timestamp;

	if (rta * 2 < eta)
		return (l_b->info.difficulty + 1);
	else if (rta > 2 * eta)
		return (l_b->info.difficulty > 0 ?
			l_b->info.difficulty - 1 : 0);

	return (l_b->info.difficulty);

}
